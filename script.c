#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
//function call
int age_Calculate(int month, int date, int year);
float BMI_calculater(float height, float wight);
float BMR_calculater(char gender, float height, float wight, int age);
float TDEE_calculater(float bmr_point, int time);
void information_Form();
void output(float bmi_point, float tdee_point);

int main(){
    char choice[4];
    printf("\n*************************************************");
    printf("\n**     Welcome to the health advice system     **");
    printf("\n*************************************************");
    printf("\nDo you want to login? [ Y/N ]\n");
    scanf("%s", &choice);
    if (toupper(choice[0]) == 'Y'){
        information_Form();
    }
    else if (toupper(choice[0]) == 'N'){
        printf("Thank you\n");
    }
}

void information_Form(){
    int date, month, year;
    char choice[4];
    char gender_2[10];

    struct information{
        float height, wight;
        int excercics_time, age;
        char gender;
    }user;

    while (1){
        printf("Fill out this Form\n");
        printf("gender(M/F): "); //เพศ
        scanf("%s", &user.gender);
        printf("Birth Date(dd/mm/yyyy): "); //อายุ คศ.
        scanf("%d/%d/%d",&date, &month, &year);
        printf("Height(cm.): "); //สูง
        scanf("%f", &user.height);
        printf("Weight(kg.): "); //น้ำหนัก
        scanf("%f", &user.wight);
        printf("Excercics time for week?(0-7): ");
        scanf("%d", &user.excercics_time); //ออกกำลังกายต่อสัปดาห์
        //setting infomation
        user.age = age_Calculate(date, month, year);
        user.gender = tolower(user.gender);
        if (user.gender == 'm'){
            strcpy(gender_2, "Male");
        }
        else if (user.gender == 'f'){
            strcpy(gender_2 ,"Female");
        }
        //Confirm_information
        printf("**************************\n");
        printf("Please Confirm information\n");
        printf("gender: %s\nHeight: %.2fcm.\nWeight: %.2fkg.\nage: %d\nexercics: %d time for a week\n", gender_2, user.height, user.wight, user.age, user.excercics_time);
        printf("Edit information?[ Y/N ]\n"); //คุณต้องการแก้ไขข้อมูลไหม
        scanf("%s", &choice);
        if (toupper(choice[0]) == 'N'){
            break;
        }
    }
    float bmi_point = BMI_calculater(user.height/100, user.wight);
    float bmr_point = BMR_calculater(user.gender, user.height, user.wight, user.age);
    float tdee_point = TDEE_calculater(bmr_point, user.excercics_time);
    output(bmi_point, tdee_point);
}

int age_Calculate(int date, int month, int year){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int num = (tm.tm_year+1900)-year;
    if (month == (tm.tm_mon+1) && date <= tm.tm_mday){
        return num;
    }
    else if (month < (tm.tm_mon+1)){
        return num;
    }
    return num-1;
}

float BMI_calculater(float height, float wight){
    float point = wight/(pow(height, 2));
    return point;
}

float BMR_calculater(char gender, float height, float wight, int age){
    if (gender == 'm'){
        float num = 66+(13.7*wight)+(5*height)-(6.8*age);
        return num;
    }
    else if (gender == 'w'){
        float num = 665+(9.6*wight)+(1.8*height)-(4.7*age);
        return num;
    }
}

float TDEE_calculater(float bmr_point, int time){
    float tdee = 0;
    if (time > 7){
        tdee = 1.9*bmr_point;
    }
    else if (time >= 6){
        tdee = 1.7*bmr_point;
    }
    else if (time >= 4){
        tdee = 1.55*bmr_point;
    }
    else if (time >= 1){
        tdee = 1.377*bmr_point;
    }
    else {
        tdee = 1.2*bmr_point;
    }
    return tdee;
}

void output(float bmi_point, float tdee_point){
    printf("*************************************************\n");
    printf("BMI: %.2f\n", bmi_point);
    int recom = 0;
    if (bmi_point >= 30){
        recom = 1;
        printf("Quite dangerous, It is at risk to be serious diseases associated with obesity.\nIf BMI is at this level, be careful of eating foods that are high in fat.\nyou should exercise regularly and if the BMI is higher than 40.0, It will show more of your obesity.\n");
    }
    else if (bmi_point >= 23){
        recom = 1;
        printf("Your weight to a lot extent.\nAlthough it's not up to the very fat level \nbut it also has a risk of obesity as well \nsuch as diabetes and high blood pressure\n");
    }
    else if(bmi_point >= 18.5){
        recom = 0;
        printf("BMI that is suitable for Thai people is between 18.5-22.9\nis classified as normal. Less risk to be obesity and other diseases.\nYou should keep your BMI at this level for as long as possible.\n");
    }
    else if (bmi_point < 18.5){
        recom = -1;
        printf("Less weight than usual is not good. If very tall but weight so low.\nMay be at risk of not receiving enough nutrients causing the body to be weak.\nEating and exercise weight training,it can help increase BMI to normal levels.\n");
    }

    if (recom == 1){
        printf("We recommend you to add weight for good health,\nCurrently you use energy %.0f kilocalories/day \nyou can control TDRR used/day %.0f kilocalories.\n", tdee_point, tdee_point+500);
    }

    else if (recom == 0){
        printf("currently you use energy %.0f kilocalories/day\n", tdee_point);
    }

    else if (recom == -1){
        printf("We recommend you to lose weight for good health,\nCurrently you use energy %.0f kilocalories/day\nyou can control TDRR used/day %.0f kilocalories.\n", tdee_point, tdee_point-500);
    }
}
