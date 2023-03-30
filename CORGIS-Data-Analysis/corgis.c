#include "corgis.h"

FILE *open_file(char *name) { // open file
    FILE *f = fopen(name, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: file not found \n", name);
        exit(1);
    }
    return f;
}

void remove_dquotes(char *word) {
    if (word[0] == '"') {
        memmove(word, word+1, strlen(word));
    }
    int end = strlen(word);
    if (word[end - 1] == '"') {
        word[end - 1] = '\0';
    }
}

float convert_float(char *item) {
    float val;
    val = atof(item);
    float rounded = roundf(val * 100) / 100;
    return rounded;
}

void validate_args(int argc, char * argv[]) { // validate args
    if (argc > NUM_ARGS) {
        fprintf(stderr, "usage: %s file \n", argv[0]);
        exit(1);
    }
}

int exists(const char *fname) {
   FILE *file;
   if ((file = fopen(fname, "r"))) {
      fclose(file);
      return 1;
    }
    return 0;
}

void validate_files(char *one, char *two) {
    if(exists(one) == 1 && exists(two) == 1) {
        return;
    } else {
        fprintf(stderr, "ERROR: file not found\n");
        exit(1);
    }
}

void validate(int argc, char *argv[], char *one, char *two) {
    validate_args(argc, argv);
    validate_files(one, two);
}

int split_by(char *str, char *args[], char delim[]) {
    char *token;
    int x = 0;
    while ((token = strsep(&str, delim)) != NULL) {
        char *item = strdup(token);
        remove_dquotes(item);
        args[x] = item;
        x ++;
    }
    free(token);
    return x;
}

info *new_info() {
    info *mydata;
    mydata = (info *)malloc(sizeof(info));
    mydata->county = (char *)malloc(sizeof(char *));
    memset(mydata -> county, '\0', sizeof(char));
    mydata->state = (char *)malloc(sizeof(char *));
    memset(mydata -> state, '\0', sizeof(char));
    mydata->ed_uni = 0.0;
    mydata->ed_hs = 0.0;
    mydata->eth_aian = 0.0;
    mydata->eth_asian = 0.0;
    mydata->eth_black = 0.0;
    mydata->eth_hisp = 0.0;
    mydata->eth_nhopi = 0.0;
    mydata->eth_bir = 0.0;
    mydata->eth_white = 0.0;
    mydata->eth_wnothl = 0.0;
    mydata->med_inc = 0;
    mydata->inc_percap = 0;
    mydata->inc_pov = 0.0;
    mydata->pop_2014 = 0;
    return mydata;
}

void load(info *mydata[], char *entries[], int idx) {
    mydata[idx]->county = entries[COUNTY];
    mydata[idx]->state = entries[STATE];
    mydata[idx]->ed_uni = convert_float(entries[UNI]);
    mydata[idx]->ed_hs = convert_float(entries[HS]);
    mydata[idx]->eth_aian = convert_float(entries[AIAN]);
    mydata[idx]->eth_asian = convert_float(entries[ASIAN]);
    mydata[idx]->eth_black = convert_float(entries[BLACK]);
    mydata[idx]->eth_hisp = convert_float(entries[HISP]);
    mydata[idx]->eth_nhopi = convert_float(entries[NHOPI]);
    mydata[idx]->eth_bir = convert_float(entries[BIRAC]);
    mydata[idx]->eth_white = convert_float(entries[WHITE]);
    mydata[idx]->eth_wnothl = convert_float(entries[WNOTHL]);
    mydata[idx]->med_inc = atoi(entries[MEDINC]);
    mydata[idx]->inc_percap = atoi(entries[PERCAP]);
    mydata[idx]->inc_pov = convert_float(entries[INCPOV]);
    mydata[idx]->pop_2014 = atoi(entries[POP2014]);
}

void load_info(info *mydata[], arraylist *mylist){
    int i;
    for (i = 0; i < mylist->numitems; i++) {
        char *args[ENT_NUM];
        // char *chunk = strdup(mylist->data[i]);
        char *entry = strdup(mylist -> data[i]);
        char delim[] = ",";
        int check = split_by(entry, args, delim);
        load(mydata, args, i);
    } 
}

void info_arr(info *data[], int lines) {
    int a;
    for (a = 0; a < lines; a++) {
        info *point = new_info();
        data[a] = point;
    }
}

void print_info(info *mydata) {
    printf("county: %s\t", mydata->county);
    printf("state: %s\t", mydata->state);
    printf("uni ed: %.2f\t", mydata->ed_uni);
    printf("hs ed: %.2f\t", mydata->ed_hs);
    //printf("\n");
    printf("aian: %.2f\t", mydata->eth_aian);
    printf("asian: %.2f\t", mydata->eth_asian);
    printf("black: %.2f\t", mydata->eth_black);
    printf("hisp: %.2f\t", mydata->eth_hisp);
    printf("not hisp: %.2f\t", mydata->eth_wnothl);
    printf("biracial: %.2f\t", mydata->eth_bir);
    printf("white: %.2f\t", mydata->eth_white);
    printf("wh not hisp: %.2f\t", mydata->eth_wnothl);
    //printf("\n");
    printf("med income: %d\t", mydata->med_inc);
    printf("income per cap: %d\t", mydata->inc_percap);
    printf("income bel poverty: %.2f\t", mydata->inc_pov);
    printf("2014 pop.: %d\t", mydata->pop_2014);
}

float ret_syb(char *input, info *data[], int i) {
    
    float a;
    if (strcmp(input,"Education.Bachelor's Degree or Higher") == 0) {
        a = data[i]->ed_uni;
    } else if (strcmp(input, "Education.High School or Higher") == 0) {
        a = data[i]->ed_hs;
    } else if (strcmp(input, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
        a = data[i]->eth_aian;
    } else if (strcmp(input, "Ethnicities.Asian Alone") == 0) {
        a = data[i]->eth_asian;
    } else if (strcmp(input, "Ethnicities.Black Alone") == 0) {
        a = data[i]->eth_black;
    } else if (strcmp(input, "Ethnicities.Hispanic or Latino") == 0) {
        a = data[i]->eth_hisp;
    } else if (strcmp(input, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
        a = data[i]->eth_nhopi;
    } else if (strcmp(input, "Ethnicities.Two or More Races") == 0) {
        a = data[i]->eth_bir;
    } else if (strcmp(input, "Ethnicities.White Alone") == 0) {
        a = data[i]->eth_white;
    } else if (strcmp(input, "Ethnicities.White Alone, not Hispanic or Latino") == 0) {
        a = data[i]->eth_wnothl;
    } else if (strcmp(input, "Income.Persons Below Poverty Level") == 0) {
        a = data[i]->inc_pov;
    } else {
        fprintf(stderr, "\t ERROR invalid field: -%s-\n", input);
        exit(1);
    }
    return a;
}

void print_info_arr(info *data[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        print_info(data[i]);
    }
}

arraylist *array_list_new() {
    arraylist *mylist;
    mylist = (arraylist *)malloc(sizeof(arraylist));
    mylist->capacity = 10;
    mylist->data = (char **)malloc(sizeof(char *) * mylist->capacity);
    memset(mylist -> data, '\0', sizeof(char *) * mylist->capacity);
    mylist->numitems = 0;
    return mylist;
}

void array_list_add_to_end(arraylist *mylist, char *new) {
    if (mylist -> numitems == mylist -> capacity) {
        mylist -> data = (char **) realloc (mylist -> data, sizeof(char *) * mylist -> capacity * 2);
        mylist -> capacity = (mylist -> capacity) * 2;
    }
    mylist -> data[mylist -> numitems] = new;
    (mylist -> numitems)++;
}

void print_array_list(arraylist *mylist) {
    int size = mylist -> numitems;
    int i;
    for (i = 0; i < size; i ++) {
        printf("%d: %s\n", i, mylist -> data[i]);
    }
}

void free_array_list(arraylist *mylist){
    int i;
    for (i = 0; i < mylist -> capacity; i ++) {
        free(mylist -> data[i]);
    }
    free(mylist->data);
    free(mylist);
}

void free_info(info *mydata) {
    free(mydata->county);
    free(mydata->state);
    free(mydata);
}

void free_info_arr(info *mydata[], int lines){
    int i;
    for (i = 0; i < lines; i ++) {
        free_info(mydata[i]);
    }
    // free(mydata);
}

int data_to_list(char *datafile, arraylist *mylist) {
    FILE *f = open_file(datafile);
    char *line = NULL;
    size_t n;
    int x = 0;
    int records = 0;
    while(getline(&line, &n, f) > 0){
        char *item = strdup(line);
        // printf("item: %s\n", item);
        if (strcmp(item, "") == 0) {
            fprintf(stderr, "empty entry at line %d\n", x);
        } else if (x == 0) {
            ;
        } else {
            array_list_add_to_end(mylist, item);
            records++;
        }
        x = x + 1;
    }
    free(line);
    fclose(f);
    return records; // return number of lines in file
}

arraylist *display(int records, arraylist *mylist) {
    info *mydata[records];
    info_arr(mydata, records); // now data holds an array that contains the important info
    load_info(mydata, mylist);
    
    int i;
    for (i = 0; i < records; i++) {
        printf("%s, %s\n", mydata[i]->county, mydata[i]->state);
        printf("\tPopulation: %d\n", mydata[i]->pop_2014);
        printf("\tEducation\n");
        printf("\t\t>= High School: %f%%\n", mydata[i]->ed_hs);
        printf("\t\t>= Bachelor's: %f%%\n", mydata[i]->ed_uni);
        
        printf("\tEthnicity Percentages\n");
        printf("\t\tAmerican Indian and Alaska Native: %f%%\n", mydata[i]->eth_aian);
        printf("\t\tAsian Alone: %f%%\n", mydata[i]->eth_asian);
        printf("\t\tBlack Alone: %f%%\n", mydata[i]->eth_black);
        printf("\t\tHispanic or Latino: %f%%\n", mydata[i]->eth_hisp);
        printf("\t\tNative Hawaiian and Other Pacific Islander Alone: %f%%\n", mydata[i]->eth_nhopi);
        printf("\t\tTwo or More Races: %f%%\n", mydata[i]->eth_bir);
        printf("\t\tWhite Alone: %f%%\n", mydata[i]->eth_white);
        printf("\t\tWhite Alone, not Hispanic or Latino: %f%%\n", mydata[i]->eth_wnothl);
        
        printf("\tIncome\n");
        printf("\tMedian Household: %d\n", mydata[i]->med_inc);
        printf("\tPer Capita: %d\n", mydata[i]->inc_percap);
        printf("\tBelow Poverty Level: %f%%\n", mydata[i]->inc_pov);
        free_info(mydata[i]);
    }
    return mylist;
}

arraylist *filter(char *args[], int records, arraylist *mylist) {
    info *data[records];
    info_arr(data, records); // now data holds an array that contains the important info
    load_info(data, mylist);
    
    arraylist *new;
    new = array_list_new();
    int matches = 0;
    char *field = args[1];
    char *gle = args[2];
    float num = convert_float(args[3]);
    int i;
    for (i = 0; i < records; i++) {
        float fval = ret_syb(field, data, i);
        if (strcmp(gle, "ge") == 0) {
            if (fval >= num) {
                matches ++;
                array_list_add_to_end(new, mylist->data[i]);
            }
        } else if (strcmp(gle, "le") == 0) {
            if (fval <= num) {
                matches ++;
                array_list_add_to_end(new, mylist->data[i]);
            }
        }
        free_info(data[i]);
    }

    printf("Filter: %s %s %f (%d entries)\n", field, gle, num, matches);
    // free_info_arr(data, records);
    return new;
}

arraylist *filter_state(char *state, int records, arraylist *mylist) {
    info *data[records];
    info_arr(data, records); // now data holds an array that contains the important info
    load_info(data, mylist);

    arraylist *new;
    new = array_list_new();
    int matches = 0;
    int i;
    for (i = 0; i < records; i++) {
        if (strcmp(state, data[i]->state) == 0) {
            matches++;
            array_list_add_to_end(new, mylist->data[i]);
        }
    }
    printf("Filter: state == %s (%d entries)\n", state, matches);
    free_info_arr(data, records);
    return new;
}

void pop_field(arraylist *mylist, char *field, int records) {
    // printf("field: %s\n", field);
    info *mydata[records];
    info_arr(mydata, records); // now data holds an array that contains the important info
    load_info(mydata, mylist);
    int i;
    float pop = 0;
    for (i = 0; i < records; i++) {
        float perc = ret_syb(field, mydata, i);
        float final = perc * mydata[i] ->pop_2014;
        final = final / 100;
        pop += final;
    }
    printf("2014 %s: %0.6f\n", field, pop);
    free_info_arr(mydata, records);
}

void population_total(arraylist *mylist, int records) {
    info *mydata[records];
    info_arr(mydata, records); // now data holds an array that contains the important info
    load_info(mydata, mylist);
    int pop = 0;
    int i;
    for (i = 0; i < records; i++) {
        pop += mydata[i] -> pop_2014;
    }
    printf("2014 population: %d\n", pop);
    free_info_arr(mydata, records);
}

void percent_field(arraylist *mylist, char *field, int records) {
    info *mydata[records];
    info_arr(mydata, records); // now data holds an array that contains the important info
    load_info(mydata, mylist);
    int i;
    float pop = 0;
    float totalpop = 0;
    for (i = 0; i < records; i++) {
        float perc = ret_syb(field, mydata, i);
        float sum = perc * mydata[i]->pop_2014;
        pop += sum;
        totalpop += mydata[i]->pop_2014;
    }
    float final = (pop/totalpop);
    printf("2014 %s: percentage: %f%%\n", field, final);
    free_info_arr(mydata, records);
}

arraylist *which_op(char *cmd, info *mydata[], int records, arraylist *mylist) {
    char *fields[SIZE];
    split_by(cmd, fields, "\n:");
    char *operation = strdup(fields[0]);
    if (strcmp(operation, "display\n") == 0 || strcmp(operation, "display") == 0) {
        mylist = display(mylist ->numitems, mylist);      
    } else if (strcmp(operation, "filter") == 0) {
        mylist = filter(fields, records, mylist);
    } else if (strcmp(operation, "filter-state") == 0) {
        mylist = filter_state(fields[1], mylist -> numitems, mylist);
    } else if (strcmp(operation, "population") == 0) {
        pop_field(mylist, fields[1], records);
    } else if (strcmp(operation, "population-total") == 0) {
        population_total(mylist, mylist -> numitems);
    } else if (strcmp(operation, "percent") == 0) {
        percent_field(mylist, fields[1], records);
    }
    return mylist;
}


int main(int argc, char *argv[]){
    validate(argc, argv, argv[1], argv[2]);
    char *datafile = argv[1];
    char *opsfile = argv[2];

    arraylist *mylist;
    mylist = array_list_new();
    int records = data_to_list(datafile, mylist); // currently each item in mylist->data is a string full of data
    printf("%d records loaded \n", records);

    info *data[records];
    info_arr(data, records); // now data holds an array that contains the important info
    load_info(data, mylist);
    // print_info_arr(data, records);
    // print_array_list(mylist);
    FILE *ops = open_file(opsfile);
    char *cmd = NULL;
    size_t n;
    while (getline(&cmd, &n, ops) > 0) {
        // printf("cmd: %s\n", cmd);
        // printf("______\n");
        mylist = which_op(cmd, data, records, mylist);
        // print_array_list(mylist);
    }
    
    free_array_list(mylist);
    return 0;
}