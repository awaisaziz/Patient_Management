#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// MAX constraints on the data fields
#define MAX_STRING_LENGTH 1024
#define MAX_PHONE_LEN 13
#define MAX_POSTAL_CODE 9
#define MAX_HEALTH_CARD_NUM 17
#define BODY_TEMP 40.5

//Patient information
typedef struct Patient{
    char name[MAX_STRING_LENGTH];   //patient name
    char street_address[MAX_STRING_LENGTH];     //patient street address
    char postal_code[MAX_POSTAL_CODE];      //patient postal code
    char phone_number[MAX_PHONE_LEN];       //patient phone number
    char health_card[MAX_HEALTH_CARD_NUM];      //patient health_card
    float body_temp_celsius;       //patient body temprature in celsius
    char problem[MAX_STRING_LENGTH];        //patient problem description
    int seen_doctor;   // Tell the nurse if the patient has not been seen by the doctor -0
                    // Tells the nurse if the patient has been seen by the doctor - 1
                    //Tells the nurse if the patient has left the place without seeing the doctor - 2
                    //patient has been updated by the nurse due to immediate attention - 3
}Patient;

// Patient node linked as a link list
typedef struct Patient_Node{
    Patient patient;
    struct Patient_Node *next;
}Patient_Node;

// Get the choice from the user

void get_choice(int *choice){
    printf("Please choose one of the following\n");
    printf("1 - Add a patient\n");
    printf("2 - update patient. Such that patient has seen the doctor"\
                " or patient has left the place\n");
    printf("3 - Search a specific patient by name\n");
    printf("4 - Patient needs immediate attention. Sent him/her first to the doctor\n");
    printf("5 - Print an updated list of patient that are left to be seen\n");
    printf("6 - Exit this program\n");
    scanf("%d", choice);
    getchar();
}

// Get info from the patient
void get_info(Patient *patient){
    printf("****************************************************\n");
    printf("Name of the patient: ");
    fgets(patient->name, MAX_STRING_LENGTH, stdin);
    printf("Street address of the patient: ");
    fgets(patient->street_address, MAX_STRING_LENGTH, stdin);
    printf("Postal Code of the patient: ");
    fgets(patient->postal_code, MAX_STRING_LENGTH, stdin);
    printf("Phone number of the patient: ");
    fgets(patient->phone_number, MAX_STRING_LENGTH, stdin);
    printf("Health card number of the patient: ");
    fgets(patient->health_card, MAX_STRING_LENGTH, stdin);
    printf("Body temprature of the patient: ");
    scanf("%f", &patient->body_temp_celsius);
    getchar();
    printf("Issue with the patient: ");
    fgets(patient->problem, MAX_STRING_LENGTH, stdin);
    patient->seen_doctor = 0;
    printf("****************************************************\n");
    return;

}

// Get a node
Patient_Node *get_node(void){
    Patient_Node *node = NULL;
    node = (Patient_Node *) calloc(1, sizeof(Patient_Node));

    if (node == NULL){
        printf("-------------------------------------------------------\n");
        printf("Sorry there is no more space left to store the data :)\n");
        printf("-------------------------------------------------------\n");
        return NULL;
    }
    node ->next = NULL;
    return node;
}

// Insert at tail to add new patient
 Patient_Node *insert_at_tail(Patient_Node *head, Patient_Node *node, Patient *new_patient){
    Patient_Node *p = NULL;

    strcpy(node ->patient.name, new_patient -> name);
    strcpy(node ->patient.street_address, new_patient ->street_address);
    strcpy(node ->patient.postal_code, new_patient ->postal_code);
    strcpy(node ->patient.phone_number, new_patient ->phone_number);
    strcpy(node ->patient.health_card, new_patient ->health_card);
    strcpy(node ->patient.problem, new_patient ->problem);
    node ->patient.body_temp_celsius = new_patient ->body_temp_celsius;
    node ->patient.seen_doctor = new_patient ->seen_doctor;

    if (head == NULL){
         return node;
    }

    // Insert at head if temp > BODY_TEMP
    if (node ->patient.body_temp_celsius > BODY_TEMP){
        node -> next = head;
        return node;
    }
    
    // Initialize the head pointer
    p = head;
    while (p ->next != NULL){
        p = p ->next;
    }
    p -> next = node;
    return head;
}

// Print one node (patient)
void print(Patient_Node *p){
    printf("*****************************************************\n");
    printf("Name: %s", p ->patient.name);
    printf("Street address: %s", p->patient.street_address);
    printf("Postal Code: %s", p->patient.postal_code);
    printf("Phone Number: %s", p->patient.phone_number);
    printf("Health card Number: %s", p->patient.health_card);
    printf("Body Temperature: %0.2f\n", p->patient.body_temp_celsius);
    printf("Issue: %s", p->patient.problem);
    printf("*****************************************************\n");
    return;
}

// Print the entire updated list
void print_patient_list(Patient_Node *head){
    Patient_Node *p = NULL;

    if (head == NULL){
        printf("*****************************************************\n");
        printf("There is nothing to print\n");
        printf("*****************************************************\n");
        return;
    }
    
    p = head;
    while (p != NULL){
        print(p);
        p = p ->next;
    }
    return;
}

 // Search specific patient by name
void search_by_name(Patient_Node *head){
    Patient_Node *p = NULL;
    char name[MAX_STRING_LENGTH];

    if (head == NULL){
        printf("------------------------------------------------------\n");
        printf("No patient present in the list \n");
        printf("------------------------------------------------------\n");
        return;
    }
    printf("------------------------------------------------------\n");
    printf("Please provide a name: ");
    fgets(name, MAX_STRING_LENGTH, stdin);
    printf("------------------------------------------------------\n");

    p = head;
    while (p != NULL){
        if (strcmp(p ->patient.name, name) == 0){
            print(p);
            return;
        }
        p = p ->next;
    }

    printf("------------------------------------------------------\n");
    printf("No  such patient present in the list \n");
    printf("------------------------------------------------------\n");
    return;
}

// Update patient after seeing doctor
void update_patient(Patient_Node *head){
    Patient_Node *p = NULL;
    int update = 0;
    char name[MAX_STRING_LENGTH];

    if (head == NULL){
        printf("------------------------------------------------------\n");
        printf("There is nothing to update\n");
        printf("------------------------------------------------------\n");
        return;
    }

    print_patient_list(head);
    printf("------------------------------------------------------\n");
    printf("Pick a name from the above list\n");
    printf("Please provide a name: ");
    fgets(name, MAX_STRING_LENGTH, stdin);
    printf("------------------------------------------------------\n");

    p = head;
    while (p != NULL){
        if (strcmp(p ->patient.name, name) == 0){
            print(p);
            while (update != 3){
                printf("------------------------------------------------------\n");
                printf("Choose one of the following\n");
                printf("0 - Patient is waiting for the doctor");
                printf("1 - Doctor has seen the patient\n");
                printf("2 - patient has left the place without seeing the doctor\n");
                printf("3 - Exit no more changes available\n");
                printf("Choose: ");
                scanf("%d", &update);
                getchar();
                printf("------------------------------------------------------\n");
                if (update == 0){
                    printf("------------------------------------------------------\n");
                    printf("Updated the list\n");
                    printf("------------------------------------------------------\n");
                } else if (update == 1){
                    p ->patient.seen_doctor = update;
                } else if (update == 2){
                    p ->patient.seen_doctor = update;
                }
            }
            return;
        }
        p = p ->next;
    }

    printf("------------------------------------------------------\n");
    printf("No  such patient present in the list \n");
    printf("------------------------------------------------------\n");
    return;
}

// Immediate attention adding by the nurse
Patient_Node *immediate_attention(Patient_Node *head){
    Patient_Node *node = NULL;
    char name[MAX_STRING_LENGTH];
    bool find = true;
    int check = 1;

    while (check != 0 && find) {
        printf("------------------------------------------------------\n");
        printf("Here 0 means - Yes and 1 means - NO\n");
        printf("Choose the following option\n");
        printf("0 - Add patient to the list\n");
        printf("1 - Search patient in the list\n");
        scanf("%d", &check);
        getchar();
        printf("------------------------------------------------------\n");
        if (check == 0){
            // Get information from the patient
            // get a node
            node = get_node();
            get_info(&node->patient);

            node ->next = head;
            return node; 
        } else if (check == 1){
            find = false;
        }
    }

    if (head == NULL){
        printf("------------------------------------------------------\n");
        printf("There is no patient currently in the list\n");
        printf("------------------------------------------------------\n");
        return NULL;
    }

    print_patient_list(head);
    printf("------------------------------------------------------\n");
    printf("Pick a name from the above list\n");
    printf("Please provide a name: ");
    fgets(name, MAX_STRING_LENGTH, stdin);
    printf("------------------------------------------------------\n");

    // remain unchange if updating head
    if (strcmp(head ->patient.name, name) == 0){
        return head;
    }

    node = head;
    while (node != NULL){
        if (strcmp(node ->patient.name, name) == 0){
            print(node);
            node -> next = head;
            return node;
        }
        node = node ->next;
    }
    printf("------------------------------------------------------\n");
    printf("There is no such person in the list\n");
    printf("------------------------------------------------------\n");
    return head;
}

// Printing full updated list
Patient_Node *updated_list(Patient_Node *head){
    Patient_Node *p = NULL;
    Patient_Node *q = NULL;

    if (head == NULL){
        printf("------------------------------------------------------\n");
        printf("No patient present in the list \n");
        printf("------------------------------------------------------\n");
        return NULL;
    }
    // update the exsiting list
    p = head;
    while (p ->patient.seen_doctor != 0){
        q = p->next;
        free(p);
        p = q;
    }

    return p;
}

// Delete the entire list
void delete_list(Patient_Node *head, FILE *fptr){
    Patient_Node *p = NULL;
    Patient_Node *q = NULL;

    if (head == NULL){
        return;
    }

    p = head;
    while(p != NULL){
        q = p -> next;
        fprintf(fptr, "Name: %sStreet_address: %sPostal_code: %sPhone_number: %sHealth_Card: %s"\
        "Body_tempretaure_in_Celsius: %0.2f \nDescription of the problem: %s\n", p ->patient.name, \
        p ->patient.street_address, p ->patient.postal_code, p ->patient.phone_number, \
        p ->patient.health_card, p ->patient.body_temp_celsius, p->patient.problem);
        free(p);
        p = q;
    }
    return;
}

int main(){

    FILE *fptr;     // Pointer for the file
    fptr = fopen("test.txt", "w");  //Open a file to write the data

    Patient patient; // patient came in
    Patient_Node *one_patient; // a pointer to a new node of type 'Patient'
    Patient_Node *head = NULL; // head pointer
    int choice = 1;
    /* I will update my list using this field: 'seen_doctor'*/
    while (choice != 6){

        // Get a choice from the user
        get_choice(&choice);

        if (choice == 1){
            one_patient = get_node(); // get a new node
            
            // Get information from the patient
            get_info(&patient);

            // insert the node at the tail
            head = insert_at_tail(head, one_patient, &patient);
        } else if (choice == 2){
            // update the patient list
            update_patient(head);
        } else if (choice == 3){
            // search a specific patient
            search_by_name(head);
        } else if (choice == 4){
            // emergiency service required by the patient
            head = immediate_attention(head);
            /* There is a problem in this function that causes
            
            */

        } else if (choice == 5){
            // prints the new updated list
            head = updated_list(head);
            print_patient_list(head);
        }
    }


    // delete the full list
    delete_list(head, fptr);
    // close the file
    fclose(fptr);

    return 0;
}