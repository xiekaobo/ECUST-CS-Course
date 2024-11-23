/* dbms1.cpp :  Database Manage System(1) -- Create Table.  */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SIZE 50		/*表中所含字段最大长度*/
#define FILE_NAME_LENGTH 15		/*文件名最大长度*/
#define FIELD_NAME_LENGTH 15	/*字段名最大长度*/	

typedef struct {
  char sFieldName[FIELD_NAME_LENGTH];
  char sType[8];
  int iSize;
  char bKey;
  char bNullFlag;
  char bValidFlag;
  } TableMode,*PTableMode;

void main()
{
   TableMode tempTM;
   TableMode FieldSet[MAX_SIZE];
   FILE *fp;
   int tempi,iNum;  /*iNum is the number of the Field*/
   char tempc;
   char dbf[FILE_NAME_LENGTH],tname[FILE_NAME_LENGTH],temptn[FILE_NAME_LENGTH];
   int bFound;  /*found the table */

   printf("\n*********** Database Manage System Design (1)- Create&View Table ************ ");
   printf("\n      *********** ECUST by LZH ************ ");
   while(1){
	   iNum=0;
	   printf("\n");
	   printf("\n");
	   printf("\n");
	   printf("\n        ********************************* ");
	   printf("\n");
	   printf("\n              0 -Create new table");
	   printf("\n              1 -View tables");
	   printf("\n              2 -Exit");
	   printf("\n");
	   printf("\n        ********************************* ");
	   printf("\nEnter your choice: ");
	   tempc=getch();
	   while(tempc!='0'&&tempc!='1'&&tempc!='2')tempc=getch();
	   printf("%c",tempc);

	  switch(tempc){
	  case '0':
		   printf("\n\n******** Creat New Table ********");
		   printf("\ninput New Table Name (MAX char[15]): ");
		   scanf("%15s",tname);
		   do{
				printf("\ninput Field Name (MAX char[15]): ");
				scanf("%15s",tempTM.sFieldName);
				printf("\ninput Field Type (MAX char[8]): ");
				scanf("%8s",tempTM.sType);
				printf("\ninput Field Size (int): ");
				scanf("%d",&tempTM.iSize);
				printf("\nKey field? (y -Yes, n -No): ");
				tempTM.bKey=getch();
				while(tempTM.bKey!='y'&&tempTM.bKey!='n')tempTM.bKey=getch();
				printf("%c",tempTM.bKey);
				printf("\nValue Null or Not? (y -Yes, n -No): ");
				tempTM.bNullFlag=getch();
				while(tempTM.bNullFlag!='y'&&tempTM.bNullFlag!='n')tempTM.bNullFlag=getch();
				printf("%c",tempTM.bNullFlag);
				tempTM.bValidFlag='y';
				FieldSet[iNum]=tempTM;
				iNum++;
				printf("\nContinue? (y -Yes, n -No): ");
			    tempc=getch();
			    while(tempc!='y'&&tempc!='n')tempc=getch();
			    printf("%c",tempc);
			  }while(tempc=='y');

	   	    printf("\nSave to File? (y -Yes, n -No): ");
		    tempc=getch();
		    while(tempc!='y'&&tempc!='n')tempc=getch();
		    printf("%c",tempc);

		   if (tempc=='y'){
			   printf("\ninput Database File Name(.dbf) (MAX char[15]): ");
			   scanf("%15s",dbf);
			   if((fp=fopen(dbf,"ab+"))==NULL){
				   printf("open or create file error!");
				   exit(1);
			   }
			   fwrite("~",sizeof(char),1,fp);
			   fwrite(tname,sizeof(char),FILE_NAME_LENGTH,fp);
			   fwrite(&iNum,sizeof(int),1,fp);
	           fwrite(FieldSet,sizeof(TableMode),iNum,fp);
			   fclose(fp);
			   printf("\nSave Successfully!");
		   }
		   break;
	  case '1':
	  	   printf("\n\n******** View Tables ********");
		   printf("\ninput Database File Name (.dbf): ");
		   scanf("%15s",dbf);
		   if((fp=fopen(dbf,"rb")) == NULL ){
			  printf("\nFile Not Exist or Bad File!\n" );
			  break;
		   }
		   printf("\nTables in %s are as following:",dbf);
		   while(!feof(fp)){
			   tempi=fread(&tempc,sizeof(char),1,fp);
			   if(!tempi)break;
			   if(tempc!='~'){
				   printf("\n%s Database Format NOT corroct!",dbf);
				   fclose(fp);
				   exit(1);
			   }
			   fread(tname,sizeof(char),FILE_NAME_LENGTH,fp);
			   fread(&iNum,sizeof(int),1,fp);
			   printf("\n%s",tname);
			   fread(FieldSet,sizeof(TableMode),iNum,fp);
		   }
		   printf("\n");
		   printf("\ninput the Table Name to View Fields: ");
		   scanf("%15s",tname);
		   rewind(fp);
		   while(!feof(fp)){
			   bFound=0;
			   tempi=fread(&tempc,sizeof(char),1,fp);
			   if(!tempi)break;
			   fread(temptn,sizeof(char),FILE_NAME_LENGTH,fp);
			   fread(&iNum,sizeof(int),1,fp);
			   fread(FieldSet,sizeof(TableMode),iNum,fp);
			   if(strcmp(tname,temptn)==0){
				   printf("\nFound! Table Fields are as following:");
				   printf("\nFieldName\tType\tSize\tKey\tNull");
				   for(tempi=0;tempi<iNum;tempi++)
					   printf("\n%s\t%s\t%d\t%c\t%c",FieldSet[tempi].sFieldName,FieldSet[tempi].sType,
						   FieldSet[tempi].iSize,FieldSet[tempi].bKey,FieldSet[tempi].bNullFlag);
					   bFound=1;
					   break;  /*break while*/
			   }
		   }
		   if(!bFound)printf("\nNo such a table in %s",dbf);
		   fclose(fp);
		   break;
	  case '2':
		   exit(0);
	   }	/*end case*/
   }	/* end do while*/
}	/*end program*/
