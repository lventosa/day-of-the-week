#include <stdio.h>
#include <stdlib.h>

void valiDate(int, int, int, int);
int isLeap(int);
int dayCode(int);
int monthCode(int, int);
int yearCode(int, int);

int main(void){
    int day, month, year, leap, dc, mc, yc, result; /*dc, mc amd yc stand for day code, month code and year code, respectively*/
    printf("Provide date in format dd mm yyyy\n");
    scanf("%d %d %d", &day, &month, &year);

    leap=isLeap(year);
    valiDate(day, month, year, leap);
    
    dc=dayCode(day);
    mc=monthCode(month, leap);
    yc=yearCode(year, leap);

    result = (dc+mc+yc)%7;

    switch(result){
        case 1: 
            printf("The given date corresponds to a MONDAY\n");
            break;
        case 2: 
            printf("The given date corresponds to a TUESDAY\n");
            break;
        case 3: 
            printf("The given date corresponds to a WEDNESDAY\n");
            break;
        case 4: 
            printf("The given date corresponds to a THURSDAY\n");
            break;
        case 5: 
            printf("The given date corresponds to a FRIDAY\n");
            break;
        case 6: 
            printf("The given date corresponds to a SATURDAY\n");
            break;
        default: 
            printf("The given date corresponds to a SUNDAY\n");
    }

    return 0;
}

void valiDate(int day, int month, int year, int leap){
    if(day<1 || month<1 || month>12 || year<1600 || year>=2400){
        printf("Date not valid\n");
        exit(1);
    }

    if(month==2 && day>29){
        printf("February has, at most, 29 days --> Date not valid\n");
        exit(1);
    }

    if(month==2 && day==29){
        if(leap==0){
            printf("%d is not a leap year --> Date not valid\n", year);
            exit(1);
        }
    }

    if(day==31 && (month==4 || month==6 || month==9 || month==11)){
        printf("The given month doesn't have 31 days --> Date not valid\n");
        exit(1);
    }

    return;
}

int isLeap(int year){
    if(year%4 == 0){
	if(year%100 == 0 && year%400 != 0) return 0; /*Not a leap year*/
	if(year%100 == 0 && year%400 == 0) return 1; /*Leap year*/
	if(year%100 != 0 && year%400 != 0) return 1;
	}else return 0;
}

int dayCode(int day){
    return day%7;
}

int monthCode(int month, int leap){
    int mc=0; /*mc = 0 is the base case and it corresponds to May. Hence, May will not be evaluated*/
    
    if(month==1 || month==10) mc = 6;
    if(month==2 || month==3 || month==11) mc = 2;
    if(month==4 || month==7) mc = 5;
    if(month==6) mc = 3;
    if(month==8) mc = 1;
    if(month==9 || month==12) mc = 4;

    if(leap==1 && (month==1 || month==2)) mc--;

    return mc;
}

int yearCode(int year, int leap){
    int digits, add=0, yc=0, new; 

    digits = year%100;
    if(digits>=28) digits = digits%28;
    new = 2000+digits; /*Transform to 21st century, baseline*/
    

    if(leap==0){
        leap=isLeap(new-1);
        if(leap==1){
            add = 1;
            new = new-1;
        }else{
            leap=isLeap(new-2);
            if(leap==1){
                add = 2;
                new = new-2;
            }else{
                add = 3;
                new = new-3;
            }
        }
    }

    /*yc = 0, as declared, is the base case and it corresponds to 2000. Hence, 2000 will not be evaluated*/
    if(new%100==4) yc = 5;
    if(new%100==8) yc = 3;
    if(new%100==12) yc = 1;
    if(new%100==16) yc = 6;
    if(new%100==20) yc = 4;
    if(new%100==24) yc = 2;

    yc += add;

    /*Adjust for century. Baseline was 21st century. 1600's need no adjustment*/
    if(year/100==19 || year/100==21) yc += 1;
    if(year/100==18 || year/100==22) yc += 3;
    if(year/100==17 || year/100==23) yc += 5;

    return yc;
}
