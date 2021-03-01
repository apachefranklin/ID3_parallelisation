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
    pthread_exit((void *)0);
}

void *shuffle(ShufleArg *s_arg)
{

    int nkeys = 0;
    MyString *keys = malloc(s_arg->length_inputs * sizeof(keys));
    for (int i = 0; i < s_arg->length_inputs; i++)
    {
        strcpy(keys[i].value, s_arg->inputs[i].key.value);
    }

    Feature f_keys = get_unique_element(keys, s_arg->length_inputs);
    nkeys = f_keys.id;
    keys = f_keys.feature; //unique keys;

    //maintenant, on fabrique la sortie avec le nombre de cle distinct
    ShufleOutput *sf_outpouts = malloc(nkeys * sizeof(sf_outpouts));

    for (int j = 0; j < nkeys; j++)
    {
        strcpy(sf_outpouts[j].key.value, keys[j].value);
        sf_outpouts[j].values = malloc(s_arg->length_inputs * sizeof(sf_outpouts[j].values));

        for (int i = 0; i < s_arg->length_inputs; i++)
        {
            if (strcmp(sf_outpouts[j].key.value, s_arg->inputs[i].key.value))
            {
                sf_outpouts[j].values[i] = s_arg->inputs[i].value;
            }
        }
    }

    s_arg->outputs = sf_outpouts;
    s_arg->length_output = nkeys;
}