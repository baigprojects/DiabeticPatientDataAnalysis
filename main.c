#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define Maximum 300
#define CharacterNum 300




// Function that clears quotation marks
void clear(char *str)
{
  int i, j;
  for (i = j = 0; str[i]; i++, j++)
  {
    while (str[i] == '"')
    {
      i++;
    }
    str[j] = str[i];
  }
  str[j] = '\0';
}


//Function that compares strings
bool Similar(const char *sim, const char *value) {
  return !strcmp(sim, "All") || !strcmp(sim, value);
}


//Function that finds the average
double average_finder(double values[], int amount){
  double average = 0;
  double sum = 0;

  for(int i = 0; i< amount; i++){
    sum = sum + values[i];
  }
average = sum/amount;
  return average;
}

//Creates arrays
double *values(const char *locale, const char *age, const char *year, int *amount){

  int NumRows;
  char *token;
  char delimiter[] = ",\n";   
  double VInfo[Maximum]; 
  double YInfo[Maximum];

  char arrayDate[Maximum][CharacterNum], arrayGeo[Maximum][CharacterNum], arrayAge[Maximum][CharacterNum], arraySex[Maximum][CharacterNum], arrayValue[Maximum][CharacterNum];
  char row[CharacterNum];
  double *values = NULL;
  *amount = 0;
  
  FILE *file;
  file = fopen("statscan_diabetes.csv", "r");

  if (file == NULL){
    printf("ERROR!: The file does not exist\n");
    return NULL;
  }

  NumRows = 0;
  bool firstrow = true;

  while (feof(file) != true){ //continuous

    fgets(row, CharacterNum, file);
    if (firstrow)
    {
      firstrow = false;
      continue;
    }

    token = strtok(row, delimiter);

    int i = 0;
    while (token != NULL){
      switch (i)
      {

      case 0:
        strcpy(arrayDate[NumRows], token);
        clear(arrayDate[NumRows]);
        break;
      case 1:
        strcpy(arrayGeo[NumRows], token);
        clear(arrayGeo[NumRows]);
        break;
      case 3:
        strcpy(arrayAge[NumRows], token);
        clear(arrayAge[NumRows]);
        break;
      case 4:
        strcpy(arraySex[NumRows], token);
        clear(arraySex[NumRows]);
        break;
      case 13:
        strcpy(arrayValue[NumRows], token);
        clear(arrayValue[NumRows]);
        VInfo[NumRows] = atof(arrayValue[NumRows]); 
        break;

      default:
        break;
      }

      if (Similar(year, arrayDate[NumRows]) && Similar(locale, arrayGeo[NumRows]) && Similar(age, arrayAge[NumRows]) && arrayValue[NumRows][0] != '\0') {
    (*amount)++;
    values = (double*) realloc(values, sizeof(double) * (*amount));
    values[(*amount) - 1] = atof(arrayValue[NumRows]);
}
      i=i+1;
      token = strtok(NULL, delimiter); 
    }
    if (strlen(row) > 1) {
    NumRows++;
    }
  }

  fclose(file);

  printf("\n");
  return values;
}

int main() {
    // Question 1a:
    printf("Question 1a:\n");
    printf("Provincial Averages (All Age)\n");
    printf("*********************************************************");

    const char* provinces[] = {"Quebec", "Ontario", "Alberta", "British Columbia"};
    const int n_provinces = sizeof(provinces) / sizeof(char*);
    double avgs[n_provinces];
    int amount = 0;
    for (int i = 0; i < n_provinces; i++) {
        double *value = values(provinces[i], "All", "All", &amount);
        avgs[i] = average_finder(value, amount);
        printf("%s: %.2lf%%", provinces[i], avgs[i]);
        free(value);
    }

    printf("\n\n");

    // Question 1b:
    printf("\n\n\n\n\nQuestion 1b:\n");
    printf("National Average (All Ages)\n");
    printf("*********************************************************");

    double CadAVG;
    double *value = values("Canada (excluding territories)", "All", "All", &amount);
    CadAVG = average_finder(value, amount);
    printf("Canada: %.2lf%%\n\n\n", CadAVG);
    free(value);

    // Question 1c:
    printf("\n\n\n\n\n\n\nQuestion 1c:");
    const char* years[] = {"2015", "2016", "2017", "2018", "2019", "2020", "2021"};
    const int n_years = sizeof(years) / sizeof(char*);
    const char* headers[] = {"Quebec", "Ontario", "Alberta", "British Columbia", "Canada (excluding territories)"};
    const int n_headers = sizeof(headers) / sizeof(char*);
    double data[n_years][n_headers];

    for (int i = 0; i < n_years; i++) {
        printf("\n\nProvincial and National Averages (All Ages) (%s)\n", years[i]);
        printf("*********************************************************");
        for (int j = 0; j < n_headers; j++) {
            value = values(headers[j], "All", years[i], &amount);
            data[i][j] = average_finder(value, amount);
            printf("%s: %.2lf%%", headers[j], data[i][j]);
            free(value);
        }
    }


  //Question 1d
  printf("\n\n\n\n\n\n\nQuestion 1d:");
  double OntGroup1, QueGroup1, BCGroup1, AlbGroup1, CadGroup1;
  double OntGroup2, QueGroup2, BCGroup2, AlbGroup2, CadGroup2;
  double OntGroup3, QueGroup3, BCGroup3, AlbGroup3, CadGroup3;

  //Group 1
  printf("\nProvincial and National Averages (Ages 35 - 49)");
  printf("\n******************************************************");
  value = values("Ontario", "35 to 49 years", "All", &amount);
  OntGroup1 = average_finder(value, amount);
  printf("Ontario: %.2lf%%", OntGroup1);
  free(value);   
  value = values("Quebec", "35 to 49 years", "All", &amount);
  QueGroup1 = average_finder(value, amount);
  printf("Quebec: %.2lf%%", QueGroup1);
  free(value);
  value = values("British Columbia", "35 to 49 years", "All", &amount);
  BCGroup1 = average_finder(value, amount);
  printf("British Columbia: %.2lf%%", BCGroup1);
  free(value);
  value = values("Alberta", "35 to 49 years", "All", &amount);
  AlbGroup1 = average_finder(value, amount);
  printf("Alberta: %.2lf%%", AlbGroup1);
  free(value);
  value = values("Canada (excluding territories)", "35 to 49 years", "All", &amount);
  CadGroup1 = average_finder(value, amount);
  printf("Canada: %.2lf%%", CadGroup1);
  free(value);

  //Group 2
  printf("\n\nProvincial and National Averages (Ages 50- 64)");
  printf("\n******************************************************");
  value = values("Ontario", "50 to 64 years", "All", &amount);
  OntGroup2 = average_finder(value, amount);
  printf("Ontario: %.2lf%%", OntGroup2);
  free(value);   
  value = values("Quebec", "50 to 64 years", "All", &amount);
  QueGroup2 = average_finder(value, amount);
  printf("Quebec: %.2lf%%", QueGroup2);
  free(value);
  value = values("British Columbia", "50 to 64 years", "All", &amount);
  BCGroup2 = average_finder(value, amount);
  printf("British Columbia: %.2lf%%", BCGroup2);
  free(value);
  value = values("Alberta", "50 to 64 years", "All", &amount);
  AlbGroup2 = average_finder(value, amount);
  printf("Alberta: %.2lf%%", AlbGroup2);
  free(value);
  value = values("Canada (excluding territories)", "50 to 64 years", "All", &amount);
  CadGroup2 = average_finder(value, amount);
  printf("Canada: %.2lf%%", CadGroup2);
  free(value);

  //Group 3
  printf("\n\nProvincial and National Averages (Ages 65+)");
  printf("\n******************************************************");
  value = values("Ontario", "65 years and over", "All", &amount);
  OntGroup3 = average_finder(value, amount);
  printf("Ontario: %.2lf%%", OntGroup3);
  free(value);
  value = values("Quebec", "65 years and over", "All", &amount);
  QueGroup3 = average_finder(value, amount);
  printf("Quebec: %.2lf%%", QueGroup3);
  free(value);   
  value = values("British Columbia", "65 years and over", "All", &amount);
  BCGroup3 = average_finder(value, amount);
  printf("British Columbia: %.2lf%%", BCGroup3);
  free(value);
  value = values("Alberta", "65 years and over", "All", &amount);
  AlbGroup3 = average_finder(value, amount);
  printf("Alberta: %.2lf%%", AlbGroup3);
  free(value);
  value = values("Canada (excluding territories)", "65 years and over", "All", &amount);
  CadGroup3 = average_finder(value, amount);
  printf("Canada: %.2lf%%", CadGroup3);
  free(value);

// Q2
// Variables for question 2
double max_avg, min_avg;
printf("\n\n\n\n\n\n\n\nQuestion 2:");
// Determine the highest average and print the result
if (avgs[1] > avgs[0] && avgs[1] > avgs[3] && avgs[1] > avgs[2])
{
  max_avg = avgs[1];
  printf("\n\nHighest Average is Ontario with %.2lf%%", max_avg);
}
else if (avgs[0] > avgs[1] && avgs[0] > avgs[3] && avgs[0] > avgs[2])
{
  max_avg = avgs[0];
  printf("\n\nHighest Average is Quebec with %.2lf%%", max_avg);
}
else if (avgs[3] > avgs[1] && avgs[3] > avgs[0] && avgs[3] > avgs[2])
{
  max_avg = avgs[3];
  printf("\n\nHighest Average is British Columbia with %.2lf%%", max_avg);
}
else
{
  max_avg = avgs[2];
  printf("\n\nHighest Average is Alberta with %.2lf%%", max_avg);
}

// Determine the lowest average and print the result
if (avgs[1] < avgs[0] && avgs[1] < avgs[3] && avgs[1] < avgs[2])
{
  min_avg = avgs[1];
  printf("\nLowest average is Ontario with %.2lf%%", min_avg);
}
else if (avgs[0] < avgs[1] && avgs[0] < avgs[3] && avgs[0] < avgs[2])
{
  min_avg = avgs[0];
  printf("\nLowest average is Quebec with %.2lf%%", min_avg);
}
else if (avgs[3] < avgs[1] && avgs[3] < avgs[0] && avgs[3] < avgs[2])
{
  min_avg = avgs[3];
  printf("\nLowest average is British Columbia with %.2lf%%", min_avg);
}
else
{
  min_avg = avgs[2];
  printf("\nLowest Average is Alberta with %.2lf%%", min_avg);
}

// Q3
// Arrays for question 3
printf("\n\n\n\n\n\n\n\nQuestion 3:");
double avg_percentages[] = {avgs[1], avgs[0], avgs[3], avgs[2]};
char *prov_names[] = {"Ontario", "Quebec", "British Columbia", "Alberta"};

bool printed_above_header = false;
bool printed_below_header = false;

// Loop to print provinces with percentages above or below the national average
for (int idx = 0; idx < 4; idx++)
{
  if (avg_percentages[idx] > CadAVG)
  {
    if (!printed_above_header)
    {
      // Print header for percentages above the national average
      printf("\nProvince(s) with diabetes percentages above the national average (%.2lf%%)\n", CadAVG);
      printf("-------------------------------------------------------------------------\n");
      printed_above_header = true;
    }
    printf("%s (%.2lf%%)\n", prov_names[idx], avg_percentages[idx]);
  }
  else if (avg_percentages[idx] < CadAVG)
  {
    if (!printed_below_header)
    {
      // Print header for percentages below the national average
      printf("\n\nProvince(s) with diabetes percentages below the national average (%.2lf%%)\n", CadAVG);
      printf("-------------------------------------------------------------------------\n");
      printed_below_header = true;
    }
    printf("%s (%.2lf%%)\n", prov_names[idx], avg_percentages[idx]);
  }
}


  
    //Question 4
    double* values(const char* header, const char* subheader, const char* year, int* amount);
    double average_finder(double* values, int amount);
    
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            double* value = values(headers[j], "All", years[i], &(int){0});
            data[i][j] = average_finder(value, 1);
        }
    }
    
    // Find the highest and lowest percentages of diabetes
    double highest_percentage = 0;
    double lowest_percentage = 100;
    int highest_years[35] = {0}; 
    int lowest_years[35] = {0};
    int num_highest_years = 0;
    int num_lowest_years = 0;
    int highest_province_idx = 0;
    int lowest_province_idx = 0;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (data[j][i] > highest_percentage) {
                highest_percentage = data[j][i];
                highest_province_idx = i;
                num_highest_years = 1;
                highest_years[0] = j;
            } else if (data[j][i] == highest_percentage) {
                highest_years[num_highest_years] = j;
                num_highest_years = num_highest_years +1;
            }
            
            if (data[j][i] < lowest_percentage) {
                lowest_percentage = data[j][i];
                lowest_province_idx = i;
                num_lowest_years = 1;
                lowest_years[0] = j;
            } else if (data[j][i] == lowest_percentage) {
                lowest_years[num_lowest_years] = j;
                num_lowest_years = num_lowest_years + 1;
            }
        }
    }
    
    // Print the province(s) and year(s) with the highest percentage
      printf("Question 4:\n");
    printf("Province(s) with highest percentage of diabetes: %s\n", headers[highest_province_idx]);
    printf("Year(s): ");
    for (int i = 0; i < num_highest_years; i++) {
        printf("%s ", years[highest_years[i]]);
    }
    printf("(%.2lf%%)\n", highest_percentage);
    
    // Print the province(s) and year(s) with the lowest percentage
    printf("\nProvince(s) with lowest percentage of diabetes: %s\n", headers[lowest_province_idx]);
    printf("Year(s): ");
    for (int i = 0; i < num_lowest_years; i++) {
        printf("%s ", years[lowest_years[i]]);
    }
    printf("(%.2lf%%)\n", lowest_percentage);
    
    return 0;
  
}//end
