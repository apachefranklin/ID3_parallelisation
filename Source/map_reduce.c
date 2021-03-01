#include "../Header/tree_learnng.h"

void *reduce(ReducerArg *r_arg)
{

    double gains[r_arg->length_inputs];

    r_arg->gain = 0.0;

    for (int i = 0; i < r_arg->length_inputs; i++)
    {
        gains[i] = 0;
        for (int j = 0; j < r_arg->inputs[i].length; j++)
        {
            gains[i] += r_arg->inputs[i].values[j];
        }
        if (gains[i] > r_arg->gain)
        {
            r_arg->gain = gains[i];
            strcpy(r_arg->key.value, r_arg->inputs[i].key.value);
        }
    }
    //pthread_exit((void *)0);
}

void *shuffle(ShufleArg *s_arg)
{

    int nkeys = 0;
    MyString *keys = malloc(s_arg->length_m_outputs * sizeof(*keys));
    for (int i = 0; i < s_arg->length_m_outputs; i++)
    {
        strcpy(keys[i].value, s_arg->m_outputs[i].key.value);
    }

    Feature f_keys = get_unique_element(keys, s_arg->length_m_outputs);
    nkeys = f_keys.id;
    keys = f_keys.feature; //unique keys;

    //maintenant, on fabrique la sortie avec le nombre de cle distinct
    ShufleOutput *sf_outpouts = malloc(nkeys * sizeof(*sf_outpouts));

    int index;
    for (int j = 0; j < nkeys; j++)
    {
        strcpy(sf_outpouts[j].key.value, keys[j].value);

        sf_outpouts[j].values = malloc(s_arg->length_m_outputs * sizeof(sf_outpouts[j].values));

        index = 0;
        for (int i = 0; i < s_arg->length_m_outputs; i++)
        {
            if (strcmp(sf_outpouts[j].key.value, s_arg->m_outputs[i].key.value) == 0)
            {
                sf_outpouts[j].values[index] = s_arg->m_outputs[i].value;
                index++;
            }
        }
        sf_outpouts[j].length = index;
    }

    s_arg->outputs = sf_outpouts;
    s_arg->length_output = nkeys;
}

void *merge_map_outputs_from_map_args(ShufleArg *s_arg)
{
    //on determine la taille totale du
    s_arg->length_output = 0;
    for (int i = 0; i < s_arg->length_m_args; i++)
        s_arg->length_m_outputs += s_arg->m_args[i].npair;

    s_arg->m_outputs = malloc(s_arg->length_output * sizeof(*s_arg->m_outputs));

    int counter = 0;
    for (int i = 0; i < s_arg->length_m_args; i++)
    {
        for (int j = 0; j < s_arg->m_args[i].npair; j++)
        {
            s_arg->m_outputs[counter].value = s_arg->m_args[i].output[j].value;
            strcpy(s_arg->m_outputs[counter].key.value, s_arg->m_args[i].output[j].key.value);
            counter++;
        }
    }
}