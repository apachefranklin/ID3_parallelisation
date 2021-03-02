#include "../Header/tree_learnng.h"

void test_parallel_decision_tree(ShufleArg sf_arg)
{
    //test shufle
    // ShufleArg sf_arg;
    // int ninput = 6;
    // sf_arg.m_outputs = malloc(ninput * sizeof(*sf_arg.m_outputs));
    // sf_arg.length_m_outputs = ninput;

    // strcpy(sf_arg.m_outputs[0].key.value, "att1");
    // sf_arg.m_outputs[0].value = 2.0;

    // strcpy(sf_arg.m_outputs[1].key.value, "att2");
    // sf_arg.m_outputs[1].value = 1.0;

    // strcpy(sf_arg.m_outputs[2].key.value, "att1");
    // sf_arg.m_outputs[2].value = 3.0;

    // strcpy(sf_arg.m_outputs[3].key.value, "att2");
    // sf_arg.m_outputs[3].value = 5.0;

    // strcpy(sf_arg.m_outputs[4].key.value, "att3");
    // sf_arg.m_outputs[4].value = 2.0;

    // strcpy(sf_arg.m_outputs[5].key.value, "att2");
    // sf_arg.m_outputs[5].value = 9.0;

    // for (int i = 0; i < sf_arg.length_m_outputs; i++)
    // {
    //     printf("\n%15s\t%15f\n", sf_arg.m_outputs[i].key.value, sf_arg.m_outputs[i].value);
    // }

    shuffle(&sf_arg);
    puts("test shufle");
    for (int i = 0; i < sf_arg.length_output; i++)
    {
        printf("%15s\n", sf_arg.outputs[i].key.value);
        for (int j = 0; j < sf_arg.outputs[i].length; j++)
        {
            printf("\t%15f\n", sf_arg.outputs[i].values[j]);
        }
    }

    //test reduce

    ReducerArg r_arg;
    r_arg.id_reducer = 0;
    r_arg.inputs = sf_arg.outputs;
    r_arg.length_inputs = sf_arg.length_output;

    reduce(&r_arg);
    puts("test reduce");
    printf("%15s\t%15f\n", r_arg.key.value, r_arg.gain);
}
