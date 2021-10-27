#include <tree.h>

int main(int argc, char **argv)
{
    FILE *cerinte, *input, *output;
    int arr[5], i = 0;
    List *list, *clasament;

    cerinte = openFile(argv[1], "rt");
    input = openFile(argv[2], "rt");
    output = openFile(argv[3], "wt");
    for (i = 0; i < 5; i++)
        fscanf(cerinte, "%d", &arr[i]);
    fclose(cerinte);

    if (arr[0])
        list = makeList(input);
    fclose(input);

    if (arr[1])
        list = cerinta2(output, list);
    else
        printList(list, output);

    if (arr[2])
        clasament = cerinta3(output, list);

    deleteList(&list);

    if (arr[3])
        cerinta4(output, clasament);

    if (arr[4])
        cerinta5(output, clasament);

    deleteList(&clasament);
    fclose(output);
    return 0;
}
