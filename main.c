#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define max_name_lenght 40

typedef struct subject{  
  int age;
  float height, weight, BMI;
  char name[max_name_lenght]; 
}Person;
// struct to create a patient

typedef struct Node{
  Person data;
  struct Node *next;
}node;

// initialize the head of the linked list
node *head = NULL; 
typedef struct node noding;

typedef struct StackNode {
    Person data;
    struct StackNode *next;
} stack_node;
//a node is a struct that contains a data and a pointer to the next node
stack_node *stack_head = NULL;

void pushStack(Person data){
  stack_node *newNode = (stack_node *)malloc(sizeof(stack_node));
  if (newNode == NULL){
    printf("Falha na alocacao de memoria.\n");
    return;
  }
  newNode->data = data;
  newNode->next = stack_head;
  stack_head = newNode;
}

Person popStack(){
  if(stack_head == NULL){
    printf("A pilha esta vazia.\n");
    Person emptyPerson = {"", 0, 0, 0};
    return emptyPerson;
  }

  //code for temporary data that keeps the data of the node that is being popped
  //this is done to avoid losing the data of the node that is being popped
  //and to free the memory of the node that is being popped
  stack_node *temp = stack_head;
  stack_head = stack_head->next;
  Person data = temp->data;
  free(temp);
  return data;
}

int isStackEmpty(){
  return stack_head == NULL;
}

typedef struct{
  node *top_element;
}Stack;

//function to calculate BMI
//formula: weight / (height * height)
//weight is in kilograms, height is in meters
//BMI is a measure of body fat and is used to assess healthy weight status
void calculateBMI(Person *patient){
  patient->BMI = patient->weight / (patient->height * patient->height);
}


//function to edit patient data
//this function is used to edit the patient data
//it asks the user to enter the patient's name and then it
//searches for the patient in the linked list
//if the patient is found, it asks the user to enter the
//new data for the patient and updates the linked list
//if the patient is not found, it prints an error message
void editPatient() {
  char nameInput[max_name_lenght];
  if (head == NULL) {
    printf("No patients to edit.\n");
    return;
  }
  printf("Enter the name of the patient to edit: ");
  scanf("%s", nameInput);

  node *patient = head;
  while (patient != NULL) {
    if (strcmp(patient->data.name, nameInput) == 0) {
      printf("Paciente encontrado. Siga as instrucoes.\n\n");
      printf("========W========\n");
      printf("Digite o novo nome:\n");
      scanf("%s", patient->data.name);
      
      printf("Digite a nova idade: ");
      scanf("%d", &patient->data.age);

      printf("Digite a nova altura: ");
      scanf("%f", &patient->data.height);

      printf("Digite o novo peso: ");
      scanf("%f", &patient->data.weight);

      calculateBMI(&patient->data);
      printf("========W========\n\n");
      printf("Detalhes do paciente alterados.\n");
      return;
    }
    patient = patient->next;
  }
  printf("Paciente nao encontrado.\n");
}

//insert patient function
//this function is used to insert a new patient into the linked list
void insertPatient(){
  node *newNode = (node*)malloc(sizeof(node));
  if (newNode == NULL)
  {
    printf("Falha na alocacao de memoria.\n");
    return;
  }
  printf("========W========\n");
  //for gangsters
  printf("Digite o nome do paciente: ");
  scanf("%s", newNode->data.name);
  printf("Digite a idade do paciente: ");
  scanf("%d", &newNode->data.age);
  printf("Digite a altura do paciente(Em metros): ");
  scanf("%f", &newNode->data.height);
  printf("Digite o peso do paciente(em quilos): ");
  scanf("%f", &newNode->data.weight);
  calculateBMI(&newNode->data);
  //assigns info to node locations
  calculateBMI(&newNode->data);
  newNode->next = head;
  head = newNode;
  printf("Paciente adicionado.\n");
  //newNode goes to next
  printf("========W========\n");
}

//function to display patient data
//this function is used to display the patient data
void displayPatients(){
  if(head == NULL)
  {
    printf("Sem pacientes para mostrar.\n");
    return;
  }
  node *patient = head;
while (patient != NULL)
  {
    printf("========W========\n");
  printf("|Nome: %s\n|Idade: %d\n|Altura: %.2f\n|Peso: %.2f\n|IMC: %.2f\n", patient->data.name, patient->data.age, patient->data.height, patient->data.weight, patient->data.BMI);
    printf("========W=========\n\n");
    patient = patient->next;
  }
}

//function to delete patient data
//this function is used to delete the patient data
void deletePatient(){
  if (head == NULL){
    printf("Sem pacientes para apagar.\n");
    return;
  }
  char name[max_name_lenght];
  printf("Digite o nome do paciente para apagar: ");
  scanf("%s", name);

  node *patient = head;
  node *previous = NULL;

  while (patient != NULL && strcmp(patient->data.name, name) != 0){
    previous = patient;
    patient = patient->next;
  }
  if (patient == NULL){
    printf("Paciente nao foi encontrado.\n");
    return;
  }
  if (previous == NULL){
    head = patient->next;
  } else {
    previous->next = patient->next;
  }

  pushStack(patient->data);
  free(patient);

  printf("Paciente apagado com sucesso.\n");
}

//function to undo patient data
//this function is used to undo the patient data
//it searches for the patient in the linked list
//if the patient is found, it undoes the patient's data
//if the patient is not found, it prints an error message
void undoDelete(){
  if(isStackEmpty()){
    printf("Sem pacientes para reverter.\n");
    return;
  }

Person restoredPatient = popStack();
  node *newNode = (node*)malloc(sizeof(node));
  if (newNode == NULL){
    printf("Nao foi possivel alocar.\n");
    return;
  }

  newNode->data = restoredPatient;
  newNode->next = head;
  head = newNode;

  printf("Paciente reustarado.\n");  
}


//function to search patient data
//this function is used to search for a patient in the linked list
//it asks the user to enter the patient's name and then it
//searches for the patient in the linked list
//if the patient is found, it prints the patient's data
//if the patient is not found, it prints an error message
void searchPatient() {
    char nameInput[max_name_lenght];
    if (head == NULL) {
        printf("Sem pacientes para buscar.\n");
        return;
    }
    printf("Digite o nome do paciente para buscar: ");
    scanf("%s", nameInput);

    node *patient = head;
    while (patient != NULL) {
        if (strcmp(patient->data.name, nameInput) == 0) {
          printf("\nPaciente encontrado.\n\n");
          printf("========W========\n");
          printf("|Nome: %s\n|Idade: %d\n|Altura: %.2f\n|Peso: %.2f\n|IMC: %.2f\n", patient->data.name, patient->data.age, patient->data.height, patient->data.weight, patient->data.BMI);
            printf("========W=========\n\n");
            return;
        }
        patient = patient->next;
    }
    printf("Paciente nao foi encontrado, use a opcao 2 para saber o nome exatos de pacientes.\n");
}

//function see BMI rating
//this function is used to see the BMI rating of a patient
//it asks the user to enter the patient's name and then it
//searches for the patient in the linked list
//if the patient is found, it prints the patient's BMI rating
//if the patient is not found, it prints an error message
void seeBMIrating() {
    char nameInput[max_name_lenght]; 
    if (head == NULL) {
        printf("Nao ha pacientes adicionados.\n");
        return;
    } else {
        printf("Digite o nome do paciente: ");
       scanf("%s", nameInput);
        node* patient = head;
        while (patient != NULL) {
            if (strcmp(patient->data.name, nameInput) == 0) {
                if (patient->data.BMI < 18.5) {
                    printf("O paciente esta abaixo do peso ideal.\n\n");
                } else if (patient->data.BMI <= 24.9) {
                    printf("O paciente esta no peso ideal.\n\n");
                } else if (patient->data.BMI <= 29.9) {
                    printf("O paciente esta acima do peso.\n\n");
                } else if(patient->data.BMI <=34.9) {
                    printf("O paciente esta com obesidade grau I.\n\n");
                } else if(patient->data.BMI <=39.9){
                  printf("O paciente esta com obesidade grau II.\n\n");
                } else{
                  printf("O paciente esta com obesidade grau III.\n\n");
                }
                return;
            }
            patient = patient->next;
          //patient is the node that is being checked
        }
        printf("O paciente nao foi encontrado.\n");
    }
}


//this is the main function
//it cooks
int main(void){
  int choice;
  noding *head;
  head = (noding*)malloc(sizeof(node));
  do{
printf("░██╗░░░░░░░██╗░░░░░░██████╗░░░░░░░██╗░░██╗\n");
printf("░██║░░██╗░░██║░░░░░░██╔══██╗░░░░░░╚██╗██╔╝\n");
printf("░╚██╗████╗██╔╝█████╗██████╦╝█████╗░╚███╔╝░\n");
printf("░░████╔═████║░╚════╝██╔══██╗╚════╝░██╔██╗░\n");
printf("░░╚██╔╝░╚██╔╝░░░░░░░██████╦╝░░░░░░██╔╝╚██╗\n");
printf("░░░╚═╝░░░╚═╝░░░░░░░░╚═════╝░░░░░░░╚═╝░░╚═╝\n\n");

    printf("\t  Bem vindo a calculadora de IMC.\n\n");

    printf("\t ---Sistema de gerenciamento----\n");
    printf("\t |1. Adicionar Paciente        |\n");
    printf("\t |2. Mostrar Pacientes         |\n");
    printf("\t |3. Deletar Pacientes         |\n");
    printf("\t |4. Reustarar Paciente Apagado|\n");
    printf("\t |5. Editar paciente           |\n");
    printf("\t |6. Buscar Paciente           |\n");
    printf("\t |7. Classificacao do IMC      |\n");
    printf("\t |0. Sair                      |\n");
    printf("\t |Digite o numero da opcao:    |\n");
    printf("\t ===============================\n");
    scanf("%d", &choice);

    switch(choice){
      case 1:
        insertPatient();
        //we insert and it calculates BMI of patients putting them into 2 stack lists (overweight and underweight)
        system ("clear");
      break;  


      case 2:
        system ("clear");
        displayPatients();
        //tell the user to choose either overweight or underweight 

      break;


      case 3:
        deletePatient();
        //just a delete function
        system ("clear");
      break;


      case 4:
        undoDelete();
        //undo the deleted section
        system ("clear");
      break;
      
      case 5:
        system("clear");
        displayPatients();
        editPatient();
        //just like inserting the patient but instead of calculating BMI, it edits the patient's info
      break;

      case 6:
        system ("clear");
        searchPatient();
        //search patients by name
      break;

      case 7:
        system("clear");
        displayPatients();
        seeBMIrating();
        //see the BMI rating of a given patient
      break;

      default:
        printf("Nao e uma opcao, escolha de novo.\n");
        //this is if the user types something not implemented
        break;

      case 0:
        printf("Saindo...\n");
      break;
    }
  } while(choice != 0);

  return 0;
}
