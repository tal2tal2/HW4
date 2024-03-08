#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct student* student;
typedef struct grade* grade;
typedef struct grades* grades;
struct grade{
    char* name;
    int value;
};
struct grades {
    struct list* students;
    student tmp;
};
struct student {
    char* name;
    int id;
    struct list* grades;
    grade tmp;
};

int student_clone(student s, student* output){
    struct student* clone = malloc(sizeof (struct student));
    if (clone==NULL){
        free(clone);
        return 1;
    }
    clone->id = s->id;
    clone->name = strcpy(clone->name,s->name);
    clone->grades = s->grades;
    clone->tmp = malloc(sizeof (struct grade));
    if(clone->tmp==NULL||clone->name==NULL){
        free(clone->tmp);
        free(clone->name);
        free(clone);
        return 1;
    }
    *output = clone;
    return 0;
}
void student_destroy(student s){
    if(s!=NULL) {
        free(s->name);
        free(s->tmp);
        if (s->grades != NULL) {
            list_destroy(s->grades);
        }
        free(s);
    }
}
struct grades* grades_init(){
    struct grades* g = malloc(sizeof (struct grades));
    if (g==NULL){
        free(g);
        return NULL;
    }
    g->tmp = malloc(sizeof (struct student));
    g->students = list_init((element_clone_t) student_clone, (element_destroy_t) student_destroy);
    if(g->tmp==NULL||g->students==NULL){
        free(g->tmp);
        free(g->students);
        free(g);
        return NULL;
    }
    g->tmp->grades = NULL;
    return g;
}
void grades_destroy(grades grades){
    if(grades!=NULL)
    {
        list_destroy(grades->students);
        free(grades);
    }
}
struct iterator* check_grades(grades grades, int id){
    if(grades==NULL)
    {
        return NULL;
    }
    struct iterator* i = list_begin(grades->students);
    while (i!=NULL)
    {
        if(((student)list_get(i))->id==id) {
            return i;
        }
        i = list_next(i);
    }
    return NULL;
}
int grades_add_student(grades grades, const char *name, int id){
    if(grades!=NULL && check_grades(grades,id)==NULL) {
        strcpy(grades->tmp->name, name);
        grades->tmp->id = id;
        list_push_back(grades->students, grades->tmp);
        return 0;
    }
    return 1;
}
int grade_clone(grade input,grade* output){
    grade g = malloc(sizeof (struct grade));
    if(g==NULL){
        free(g);
        return 1;
    }
    strcpy(g->name,input->name);
    g->value = input->value;
    *output = g;
    return 0;
}
void grade_destroy(grade g){
    free(g->name);
    free(g);
}
int grades_add_grade(grades grades,
                     const char *name,
                     int id,
                     int grade){
    student a = list_get(check_grades(grades,id));
    if(grade>100||grade<0){
        return 1;
    }
    if(a->grades==NULL){
        a->grades=list_init((element_clone_t) grade_clone, (element_destroy_t) grade_destroy);
        strcpy(a->tmp->name,name);
        a->tmp->value = grade;
        return list_push_back(a->grades,a->tmp);
    }
    struct iterator* i = list_begin(a->grades);
    while (i!=NULL)
    {
        if(!strcmp(((struct grade*)list_get(i))->name,name)) {
            return 1;
        }
        i = list_next(i);
    }
    strcpy(a->tmp->name,name);
    a->tmp->value = grade;
    return list_push_back(a->grades,a->tmp);
}
float grades_calc_avg(grades grades, int id, char **out){
    float counter = 0;
    float total = 0;
    struct iterator* i = check_grades(grades,id);
    if(i==NULL){
        *out = NULL;
        return -1;
    }
    student s = list_get(i);
    i = list_begin(s->grades);
    while(i!=NULL){
        total += (float)((grade)list_get(i))->value;
        counter++;
    }
    strcpy(*out,s->name);
    return (total/counter);
}
void print_student(student s){
    printf("%s %d: ",s->name,s->id);
    struct iterator* i = list_begin(s->grades);
    while(i!=NULL){
        grade g = list_get(i);
        printf("%s %d, ",g->name,g->value);
        i = list_next(i);
    }
}
int grades_print_student(struct grades *grades, int id){
    struct iterator* i = check_grades(grades,id);
    if(i ==NULL){
        return 1;
    }
    student s = list_get(i);
    printf("%s %d: ",s->name,s->id);
    print_student(s);
    return 0;
}
int grades_print_all(struct grades *grades){
    if(grades ==NULL){
        return 1;
    }
    struct iterator* i = list_begin(grades->students);
    while(i!=NULL) {
        student s = list_get(i);
        print_student(s);
        printf("\n");
        i = list_next(i);
    }
    return 0;
}