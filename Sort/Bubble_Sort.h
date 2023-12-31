void bubbleSort(int array[], int size) {

    for (int step = 0; step < (size - 1); ++step) {
        int swapped = 0;

        for (int i = 0; i < (size - step - 1); ++i) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}
