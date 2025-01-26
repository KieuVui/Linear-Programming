#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>



void Menu(){
	printf("\n\n===================MENU===================");
	printf("\n0. Thoat.");
	printf("\n1. Nhap bai toan.");
	printf("\n2. Xuat ket qua cua bai toan.");
	printf("\n3. Xuat cac tu vung va ket qua cua bai toan.");
	printf("\n==========================================");
}

void input(int *n,int *m,float c[10],float A[][10],float b[],int sign[],int *test, int free[]){
	char obj[5]; //min/max
	printf("\nNhap so bien: ");
	scanf("%d", n);
	printf("Nhap so rang buoc: ");
	scanf("%d", m);
	
	//Kiem tra xem co bien nao tu do 
	printf("\n------------------------------------------------------------\n");
	printf("\nKIEM TRA BIEN NAO TU DO (Neu la bien tu do nhap 1, neu khong nhap 0):\n");
	for(int i = 0; i<*n;i++){
		do{
		printf("Bien x%d co la bien tu do khong? ",i+1);
		scanf("%d",&free[i]);
		
		}while((free[i]!=0) && (free[i]!=1) && printf("Chi nhap 0 hoac 1!!!\n"));
	}
	
	//test kiem tra xem co can doi min/max khong
	//La min test = 1, la max test = 0
	*test = -1;
	int i,j;
	printf("\n------------------------------------------------------------\n");
	printf("\nNHAP HAM MUC TIEU:\n");
	do{
		printf("Chon min/max: ");
 		scanf("%s", obj);
        for(i = 0; i < strlen(obj); i++){
			obj[i] = tolower(obj[i]);
		}
	} while( (strcmp(obj, "min")!=0) && (strcmp(obj, "max")!=0) && printf("Chi nhap min/max!!!\n"));
 	if(strcmp(obj, "min")==0){
 		*test= 1;
	}
	else {
		*test= 0;
	}
	for(i = 0;i < *n;i++){
		printf("Nhap tham so x%d o ham muc tieu: ",i+1);
		scanf("%f",&c[i]);
	}
	if(*test==0){
		for(i = 0;i < *n;i++){
		    c[i]=-c[i];
		}
	}
	
	//Dau cua rang buoc
	char signStr[3];
	printf("\n------------------------------------------------------------\n");
	printf("\nNHAP CAC RANG BUOC:");
	for(i=0;i<*m;i++){
		printf("\n");
		for(j=0;j<*n;j++){
		    printf("Nhap tham so x%d cua rang buoc %d: ",j+1,i+1);
		    scanf("%f",&A[i][j]);
		}
		//0 la "=" 
		//1 la "<=" 
		//2 la ">="
		do{
		printf("Nhap dau cua rang cua rang buoc %d: ",i+1);
		scanf("%s",signStr);
		} while( (strcmp(signStr, "=")!=0) && (strcmp(signStr, "<=")!=0) && (strcmp(signStr, ">=")!=0) && printf("Chi nhap cac ki =, <=, >=\n"));
		if(strcmp(signStr, "=")==0){
 		   sign[i]= 0;
	    }
	    else if (strcmp(signStr, "<=")==0){
		   sign[i]= 1;
	    }
	    else {
		   sign[i]= 2;
	    }
		printf("Nhap gia tri b%d cua rang buoc %d: ",i+1,i+1);
		scanf("%f",&b[i]);
	}
}

// Dinh nghia cau truc cua mot nut trong ds lien ket
struct Node {
    char *key;
    char *value;
    struct Node* next;
};

// Ham tao nut moi trong danh sach lien ket
struct Node* createNode(const char *key, const char *value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = strdup(key); // Sao chep key vao mot vung nho moi 
    newNode->value = strdup(value); // Sao chep value vao mot vung nho moi 
    newNode->next = NULL;
    return newNode;
}

// Ham chen them mot phan tu moi trong danh sach lien ket
void insert(struct Node** head, const char *key, const char *value) {
    struct Node* newNode = createNode(key, value);
    newNode->next = *head;
    *head = newNode;
}

// Ham tim value dua tren key
char* find(struct Node* head, const char *key) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Tra ve NULL neu ko tim thay khoa
}

//ham tao danh sach lien ket giua bien ban dau va bien sau khi chuyen 
void makeList(struct Node** head,int tt[],int n,char freeName[10][3], int* numFreeVariables){
    int s=0;//kich thuoc cua danh sach lien ket
    *numFreeVariables = 0;
    int a=0;
    //freeName la danh sach chua ten bien 
    for(int i = 0; i < n; i++){
        if(tt[i]==1){
            //i=2
            char temp[3],key_1[3],key_2[3];
            temp[0]='x';temp[1]=(char) (i+1+48);temp[2]='\0';//temp=x3
            key_1[0]='x';key_1[1]=(char)(s+1+48);key_1[2]='\0';//key_1=x4
            insert(head, key_1, temp);
            (*numFreeVariables)++;
            freeName[a][0]='x';freeName[a][1]=(char)(s+1+48);freeName[a][2]='\0';
            a++;
            s++;
            key_2[0]='x';key_2[1]=(char)(s+1+48);key_2[2]='\0';//key_2=x2
            insert(head, key_2, temp);
            (*numFreeVariables)++;//kich thuoc mang freeName
            freeName[a][0]='x';freeName[a][1]=(char)(s+1+48);freeName[a][2]='\0';
            a++;
            s++;
        }
        if(tt[i]==0){
            char temp[3],key[3];
            temp[0]='x';temp[1]=(char) (i+1+48);temp[2]='\0';
            key[0]='x';key[1]=(char)(s+1+48);key[2]='\0';
            insert(head, key, temp);
            s++;
        }
    }
}

void transStandard(int *n,int *m,float c[10],float A[][10],float b[],int sign[], int tt[]){
	//check bien tu do
    for (int i = 0; i < (*n); i++) {
        if (tt[i] == 1) {
            (*n)++; // Tang n
            for (int j = (*n) - 1; j > i + 1; j--) {
                c[j] = c[j - 1]; // thay doi tham so ham muc tieu
                tt[j]=tt[j-1]; 
            }
            c[i + 1] = -c[i];
            tt[i + 1]= 0; 
            tt[i]=0; 
            
            for(int a=0;a<(*m);a++){
                for (int j = (*n) - 1; j > i + 1; j--) {
                    A[a][j]=A[a][j-1];
                }
                A[a][i+1]=-A[a][i];
            }
        }
        
    }
    
    //chuyen cac rang buoc ve dang <= 
    // dau o cac rang buoc (0 la "=",1 la "<=", 2 la ">=")
    for (int j = 0; j < (*m); j++) {
        if(sign[j]==2){
            for(int k=0;k<(*n);k++){
                A[j][k]=-A[j][k];
            }
            sign[j]==1;
            b[j] = -b[j];
        }
        if(sign[j]==0){
            (*m)++;
            int a = (*m) - 1;
            for(int i=0;i<(*n);i++){
                A[a][i]=-A[j][i];
            }
            b[a] = -b[j];
            sign[a]=1;
            sign[j]==1;            

            //sign[j+1]==1;            

        }
    }
}

void printStandard(int n,int m,float c[10],float A[][10],float b[],int sign[],int test, int tt[]){
    
    //in ham muc tieu
    if(test == 0){
    	printf("\n-min ");
	}
	else{
		printf("\nmin ");
	}
    for(int i=0;i<n;i++){
        if(i!=0 && c[i]>0){printf("+");} 
        if(c[i]==0){continue;}
        printf("%gx%d ",c[i],i+1);
    }
    //in rang buoc
    for(int i=0;i<m;i++){
        printf("\nRang buoc %d: ",i+1);
        for(int a=0;a<n;a++){
            if(a!=0 && A[i][a]>0 ){printf("+");}
            if(A[i][a]==0){continue;}
            printf("%gx%d ",A[i][a],a+1);
        }     
        if(abs(b[i])<1e-6){
        	b[i]=0;
        }
        printf("<= %g",b[i]);
    }
    printf("\n");
}


void Press()
{
	system("pause");
	system("cls");
}

//Mot thanh phan trong tu vung chua tham so va ten bien
typedef struct variableStructure{
	float coef; //he so cua bien
	char name[10]; //ten bien
}Variable;

//Tu vung
typedef struct matrixVariable{
	int numCol,numRow;
	Variable m[11][12];
}matrixVariable;

//Tao tu vung xuat phat
matrixVariable createMatrix(int n,int m,float c[10],float A[10][10], float b[10],matrixVariable matrix){
	
	//So cot cua tu vung se bang so bien cong voi he so tu do cong voi cot z 
	//VD: z =   x1+2x2 //Cot ma tran la 4 = (2+n)
	matrix.numCol=2+n;
	
	//So hang cua tu vung se bang so rang buoc cong ham muc tieu (+1)
	matrix.numRow=1+m;
	
	for(int i=0;i<(matrix.numRow);i++){
		for(int j=0;j<(matrix.numCol);j++){
			//Xet cot dau tien
			if(j==0){
				//Tham so xuat phat cua cot dau tien la 1
				(matrix.m[i][0].coef)=1;
				//Dat ten cho cot dau tien
				if(i==0){
					//dong dau tien cua cot dau co ten bien la z
					strcpy(matrix.m[0][0].name,"z");
				} else{
					//Cac dong con lai co ten bien la w1,w2,w3,...
				     char var_name[3];
				     var_name[0] = 'w';
				     var_name[1] = (char)(i+48);
				     var_name[2] = '\0';
					strcpy(matrix.m[i][0].name,var_name);
				}
			} else if(j==1){
				//Xet cot thu hai //cot he so tu do
				
				//cot he so tu do nen khong co name mac dinh la "NA"
				strcpy(matrix.m[i][1].name,"NA");
				if(i==0){
					//He so tu do cua ham muc tieu = 0
					matrix.m[0][1].coef=0;
				}else{
					//The cac he so tu do con lai lay du lieu tu mang b 
					matrix.m[i][1].coef=b[i-1];
				}
			}else{
				//Xet cac cot con lai
				
				//Cac cot co ten bien la x1,x2,x3,...
			    char var_name[3];
				var_name[0] = 'x';
				var_name[1] = (char)(j-1+48);
				var_name[2] = '\0';
				strcpy(matrix.m[i][j].name,var_name);
				
				if(i==0){
					//Dong dau tien co tham so o ham muc tieu nen lay du lieu tu mang c
					matrix.m[0][j].coef=c[j-2];
				}else{
					//Cac dong con lai lay du lieu tu ma tran A
					matrix.m[i][j].coef= - A[i-1][j-2];
				}
			}
		}
	}
	return matrix;
}

//Chon dau vao dau ra cho tu vung theo phuong phap don hinh
void simplexInputOutput(matrixVariable matrix,int* idx_input, int* idx_output){
	
	//Luu 2 ten bien de so sanh
	//Bien thu nhat la bien input/output hien tai
	//Bien thu hai la bien dang xet
	char pri_name[2][3];
	
	//input la gia tri am nhat o dong dau ma tran (khong tinh z va he so tu do)
	//output la phep chia nao nho nhat
	//input khong the chon dau vao duong nen khoi tao input = 1
	//output la phep chia co tri tuyet doi nen khong am khoi tao output = -1
	float input = 1,output = -1;
	
	//Xet dong dau tien khong tinh z va he so tu do nen xet tu cot co chi so la 2
	for(int j=2;j<(matrix.numCol);j++){
		//Luu gia tri input o vi tri dang xet
		float temp_input=matrix.m[0][j].coef;
		//Chi xet gia tri input < 0 
		if(temp_input<0){
			//Neu nhu tu vung da co gia tri input truoc do (input!=1) 
			//Thi so sanh gia tri input va gia tri input o vi tri dang xet 
			//Chon gia tri be hon
			if(input!=1&&input>temp_input){
				input=temp_input;
				*idx_input=j;
				strcpy(pri_name[0],matrix.m[0][j].name);
			}else if(input!=1 && input==temp_input){
				strcpy(pri_name[1],matrix.m[0][j].name);
				//Neu ten bien thu nhat la bien w va ten bien thu hai la x chon bien x
				//Vd: Ten bien 1: w2, ten bien 2: x2 -> Chon bien 2
				//Hoac hai ten bien cung la w hoac cung la x chon ten bien co so nho hon 
				//Vd: Ten bien 1: x2, ten bien 2: x0 -> Chon bien 2
				if((pri_name[0][0]<pri_name[1][0])||(pri_name[0][0]==pri_name[1][0]&&pri_name[0][1]>pri_name[1][1])){
					//Gan chi so bien vao moi
		    	   *idx_input=j;
		    	    //Cho ten bien thu nhat la ten bien input moi
		    	    strcpy(pri_name[0],pri_name[1]);
		    	}
			}else if(input==1){
				//Neu nhu tu vung chua co gia tri input truoc do (input==1) 
				//Lay gia tri input o vi tri dang xet 
				input=temp_input;
				*idx_input=j;
				strcpy(pri_name[0],matrix.m[0][j].name);
			}
		}
	}
	
	//Xet output tu dong co chi so la 1 (khong tinh dong ham muc tieu)
	for(int i=1;i<(matrix.numRow);i++){
		//Chi xet cac gia tri ma tu vung o vi tri [i][idx_input] < 0 
		if(matrix.m[i][(*idx_input)].coef<0){
			//Luu gia tri output o vi tri dang xet 
			float temp_output=(matrix.m[i][1].coef)/(-(matrix.m[i][(*idx_input)].coef));
			//Neu nhu tu vung da co gia tri output truoc do (output!=-1) 
			//Thi so sanh gia tri output va gia tri output o vi tri dang xet 
			//Chon gia tri be hon
			if(output!=-1 && output>temp_output){
		    	output=temp_output;
		    	*idx_output=i;
		    	strcpy(pri_name[0],matrix.m[i][0].name);
			}else if(output!=-1 && output==temp_output){
				//Neu gia tri xet output bang nhau
				//Luu ten bien thu hai la ten bien dang xet
				strcpy(pri_name[1],matrix.m[i][0].name);
				//Neu ten bien thu nhat la bien w va ten bien thu hai la x chon bien x
				//Vd: Ten bien 1: w2, ten bien 2: x2 -> Chon bien 2
				//Hoac hai ten bien cung la w hoac cung la x chon ten bien co so nho hon 
				//Vd: Ten bien 1: x2, ten bien 2: x0 -> Chon bien 2
				if((pri_name[0][0]<pri_name[1][0])||(pri_name[0][0]==pri_name[1][0]&&pri_name[0][1]>pri_name[1][1])){
					//Gan chi so bien ra moi
		    	    *idx_output=i;
		    	    //Cho ten bien thu nhat la ten bien output moi
		    	    strcpy(pri_name[0],pri_name[1]);
		    	}
		    }else if(output==-1){
				//Neu nhu tu vung chua co gia tri output truoc do (output==-1) 
				//Lay gia tri output o vi tri dang xet 
			    output = temp_output;
			    *idx_output=i;
			    //Neu chua co gia tri output thi luu ten bien o vi tri dau tien
			    strcpy(pri_name[0],matrix.m[i][0].name);
		    }
		} 
	}	
}

//Thu tu uu tien
typedef struct priority{
	int order; //Thu tu cua bien
	char name[10]; //Ten bien
}Priority;

//Thu tu uu tien cua cac bien trong tu vung
typedef struct arrayPriority{
	int count; //so luong bien
	Priority priority[20];
}arrayPriority;

//Xay dung thu tu uu tien cho cac bien trong tu vung
arrayPriority priorityOrder(matrixVariable matrix,arrayPriority pr){
	int priOrd = 0; //Khoi tao thu tu //Luc dau thu tu uu tien cua moi bien luon la 0
	pr.count = 0; //Khoi tao so bien
	
	//Them lan luot cac bien x1,x2,x3,... vao thu tu uu tien
	for(int j=2;j<(matrix.numCol);j++){
		pr.priority[priOrd].order = priOrd + 1;
		strcpy(pr.priority[priOrd].name,matrix.m[0][j].name);
		priOrd++;
		pr.count++;
	}
	
	//Tiep tuc them lan luot cac bien w1,w2,w3,... vao thu tu uu tien
	for(int i=1;i<(matrix.numRow);i++){
		pr.priority[priOrd].order = priOrd + 1;
		strcpy(pr.priority[priOrd].name,matrix.m[i][0].name);
		priOrd++;
		pr.count++;
	}
	
	return pr;
}

//Kiem tra bien do la o thu tu uu tien nao 
int checkPriority(arrayPriority pr,char c[]){
	int pri;
	for(int i=0;i<pr.count;i++){  
	    if(strcmp(pr.priority[i].name,c)==0){
	    	pri=pr.priority[i].order;
	    	break;
	    }
	}
	return pri;
}

//Chon dau vao dau ra cho tu vung theo phuong phap Bland
void blandInputOutput(matrixVariable matrix,int* idx_input, int* idx_output,arrayPriority pr){
	
	float input = 1,output = -1; 
	int priority = 0; //Khoi tao thu tu uu tien bang 0
	
	for(int j=2;j<(matrix.numCol);j++){
		float temp_input=matrix.m[0][j].coef;
		//Kiem tra thu tu uu tien cua bien o vi tri dang xet
		int priOrd = checkPriority(pr,matrix.m[0][j].name);
		//Chi xet input < 0
		if(temp_input<0){
			//Neu nhu tu vung da co gia tri input truoc do (input!=1) 
			//Thi so sanh muc do uu tien cua input va input o vi tri dang xet 
			//Chon theo muc do uu tien (muc do uu tien nao co thu tu be hon thi chon)
			if(input!=1&&priority>priOrd){
				input=temp_input;
				*idx_input=j;
				priority = priOrd;
			}else if(input==1){
				//Neu nhu tu vung chua co gia tri input truoc do (input==1) 
				//Lay gia tri input o vi tri dang xet 
				input=temp_input;
				*idx_input=j;
				priority = priOrd;
			}
		}
	}
	
	//Output tuong tu phuong phap don hinh
	char pri_name[2][3];

	for(int i=1;i<(matrix.numRow);i++){
		if(matrix.m[i][(*idx_input)].coef<0){
			float temp_output=(matrix.m[i][1].coef)/(-(matrix.m[i][(*idx_input)].coef));
			if(output!=-1 && output>temp_output){
		    	output=temp_output;
		    	*idx_output=i;
		    	strcpy(pri_name[0],matrix.m[i][0].name);
			}else if(output!=-1 && output==temp_output){
				strcpy(pri_name[1],matrix.m[i][0].name);
				if((pri_name[0][0]<pri_name[1][0])||(pri_name[0][0]==pri_name[1][0]&&pri_name[0][1]>pri_name[1][1])){
		    	    *idx_output=i;
		    	    strcpy(pri_name[0],pri_name[1]);
		    	}
		    }else if(output==-1){
			    output = temp_output;
			    *idx_output=i;
			    strcpy(pri_name[0],matrix.m[i][0].name);
		    }
		} 
	}	
}

//ham ket luan truong hop co duy nhat nghiem
void displayDistinctRoot(matrixVariable mt,int count,int test){
    printf("So buoc xoay la: %d\n",count);
    if (test ==1){
    if(abs(mt.m[0][1].coef)<1e-6){mt.m[0][1].coef=0;}
    printf("Gia tri toi uu la: %g\n",mt.m[0][1].coef);
    }
    if(test ==0){
    if(abs(mt.m[0][1].coef)<1e-6){mt.m[0][1].coef=0;}
    printf("Gia tri toi uu la: %g\n",-mt.m[0][1].coef);
    }
    printf("Nghiem toi uu la:\n");
    //cho gia tri cua nhung bien o ham muc tieu=0
   for(int j=2;j<=mt.numCol-1;j++){
       printf("%s = 0\n",mt.m[0][j].name);
   }
   for(int i=1;i<=mt.numRow-1;i++){
       if(abs(mt.m[i][1].coef)<1e-6){mt.m[i][1].coef=0;}
       printf("%s = %g\n",mt.m[i][0].name,mt.m[i][1].coef);
   }
} 

//ham ket luan neu co mot bien khuyet 
void displayOneMissing(matrixVariable mt,int count,int test){
    //tim khoang gia tri cua bien khuyet
    //dau tien cho cac bien o ham muc tieu = 0 tru bien khuyet 
    char name[10];
    for(int j=2;j<=mt.numCol-1;j++){
        if(mt.m[0][j].coef > 0 ){
            for(int i=1;i<=mt.numRow-1;i++){
                mt.m[i][j].coef=0;
            }
        }
    }
    
    //tim khoang gia tri cua bien bi khuyet 
    float min=0;
    float max=-INFINITY;
    for(int j=2;j<=mt.numCol-1;j++){
        if(mt.m[0][j].coef == 0 ){
            strcpy(name,mt.m[0][j].name);
            for(int i=1;i<=mt.numRow-1;i++){
                float temp=mt.m[i][1].coef/fabs(mt.m[i][j].coef);
                if( (mt.m[i][j].coef <0) && (max < temp)){
                    max=temp;
                }
                if( (mt.m[i][j].coef >0) && (min> (-temp))){
                    min=-(temp);
                }
            }
        }
    }
    if(max=-INFINITY)   max=INFINITY;

    printf("So buoc xoay la: %d\n",count);
    if (test =1){
    printf("Gia tri toi uu la: %g\n",mt.m[0][1].coef);
    }else {
    printf("Gia tri toi uu la: %g\n",-mt.m[0][1].coef);
    }
    printf("Khoang gia tri cua %s la tu %g den %g\n",name,min,max);
    //in gia tri cua cac nghiem con lai 
    for(int j=2;j<=mt.numCol-1;j++){
        if(mt.m[0][j].coef > 0 ){
            printf("%s = 0\n",mt.m[0][j].name);
        }
    }
    for(int i=1;i<=mt.numRow-1;i++){
        printf("%s = %g\n",mt.m[i][0].name,mt.m[i][1].coef);
    }
    
}

//ham ket luan khi co hai bien khuyet 
void displayTwoMissing(matrixVariable mt,int count,int test){
    printf("So buoc xoay la: %d\n",count);    
    if (test =1){
    printf("Gia tri toi uu la: %g\n",mt.m[0][1].coef);
    }else {
    printf("Gia tri toi uu la: %g\n",-mt.m[0][1].coef);
    }
    char name[2][10];
    int a=0;
    //luu ten cua bien khuyet
    for(int j=2;j<=mt.numCol-1;j++){
        if(mt.m[0][j].coef == 0 ){
            strcpy(name[a],mt.m[0][j].name);
            a++;
        }
    }
    
    //cac bien o ham muc tieu = 0 tru bien khuyet 
    for(int j=2;j<=mt.numCol-1;j++){
        if(mt.m[0][j].coef > 0 ){
            printf("%s = 0\n",mt.m[0][j].name);
            for(int i=1;i<=mt.numRow-1;i++){
                mt.m[i][j].coef=0;
            }
        }
    }
    printf("Thoa :");
    for(int i=1;i<=mt.numRow-1;i++){
        printf("\n%s = %g",mt.m[i][0].name,mt.m[i][0].coef);
        for(int j=2;j<=mt.numCol-1;j++){
            if (mt.m[i][j].coef==0)  continue;
            if(mt.m[i][j].coef>0) printf("+");
            printf("%g%s",mt.m[i][j].coef,mt.m[i][j].name);
        }
    }
    
     printf("\nVoi dieu kien :");
    //cac bien khuyet co dieu kien la >= 0
    printf("\n%s >= 0",name[0]);
    printf("\n%s >= 0\n",name[1]);
    for(int i=1;i<=mt.numRow-1;i++){
        for(int j=1;j<=mt.numCol-1;j++){
            if (mt.m[i][j].coef==0)  continue;
            if(mt.m[i][j].coef>0) printf("+");
            if(j==1){
                printf("%g",mt.m[i][j].coef);
            }else{
            printf("%g%s",mt.m[i][j].coef,mt.m[i][j].name);
            }
        }
        printf(">= 0\n");
    }
}

matrixVariable deleteColumn(matrixVariable mt,char* name_del){
    int idx_del=-1;
    for(int j=2;j<=mt.numCol-1;j++){
        if(strcmp(mt.m[0][j].name,name_del)==0){
            idx_del=j;
        }
    }

    for (int i = 0; i <= mt.numRow-1; i++) {
        for (int j = idx_del; j < mt.numCol - 1; j++) {
            mt.m[i][j].coef = mt.m[i][j + 1].coef;
            strcpy(mt.m[i][j].name,mt.m[i][j+1].name);
        }
    }
    mt.numCol--;
    //giam so cot sau khi xoa
    return mt;
}
// In mot lan xoay
void printIteration(matrixVariable mt){
	for(int i=0; i<(mt.numRow); i++){
		for(int j=0; j <(mt.numCol); j++){
			if(j==0){
				// In z neu la ham muc tieu
				if(i==0){
					if(strcmp(mt.m[i][j].name,"E")==0){
						printf("\nE = ");
					}else{
						printf("\nz = ");
					}	
				}
				// In ten cac bien co so neu i>0
				else{
					printf("\n%s = ", mt.m[i][j].name);
				}					
			}			
			else if(j==1){
				if(mt.m[i][j].coef == 0) {
					printf("\t  ");
				}
				else{
					printf("%.2f ", mt.m[i][j].coef);
				}					
			}
			else{
				if(mt.m[i][j].coef>0){printf("+ ");}
				if(mt.m[i][j].coef == 0) {
					printf("\t  ");
				}
				else{ 
					printf("%.2f", mt.m[i][j].coef);
					printf("%s ", mt.m[i][j].name);
				}
				if(i==0 && j==(mt.numCol-1)){
					printf("\n");
					for(int a = 0; a<mt.numCol; a++){
						printf("-------");
					}						
				}
			}
				
		}				
	}
	printf("\n");
}
//ham kiem tra xem co bien vao va bien ra hay khong de ket luan nghiem
int checkInputOutput(matrixVariable mt,int inputVar,int outputVar,int count,int test,char freeName[10][3],int size_freeName,struct Node* head){
    if (inputVar == -1 ){
        int khuyet=0;

        for(int j=2;j<=mt.numCol-1;j++){
            //neu he so bang 0 va no la bien sinh ra tu bien tu do
            if(mt.m[0][j].coef==0){
                for(int i=0;i<size_freeName;i++){
                    if(strcmp(mt.m[0][j].name,freeName[i])==0){
                        if(i%2!=0){ //truong hop he so cua x1- o ham muc tieu =0
                            //xoa cot
                            char name_del[3];
                            strcpy(name_del, freeName[i]);
                            mt=deleteColumn(mt,name_del);
                            //duyet cot dau tien de doi ten bien 
                            for(int h=1;h<=mt.numRow-1;h++){
                                //neu ten bien co so la w hoac x0 thi bo qua
                                if(mt.m[h][0].name[0]=='w' || (strcmp(mt.m[h][0].name,"x0")==0) ){
                                    continue;
                                }
                                if(strcmp(mt.m[h][0].name,freeName[i-1])==0){
                                char *result = find(head, mt.m[h][0].name);
                                strcpy(mt.m[h][0].name, result);
                                break;
                                }
                            }
                        }else{ //truong hop he so cua x1+ o ham muc tieu = 0 
                            //doi dau hang cua x1-
                            for(int h=1;h<=mt.numRow-1;h++){
                                //dau tien can tim hang do va doi dau cua hang
                                if(strcmp(mt.m[h][0].name,freeName[i+1])==0){
                                    for(int k=1;k<=mt.numCol-1;k++){
                                        mt.m[h][k].coef=-mt.m[h][k].coef;
                                    }
                                }
                            }
                            //xoa cot
                            char name_del[3];
                            strcpy(name_del, freeName[i]);
                            mt=deleteColumn(mt,name_del);
                            //duyet cot dau tien de doi ten bien 
                            for(int h=1;h<=mt.numRow-1;h++){
                                //neu ten bien co so la w hoac x0 thi bo qua
                                if(mt.m[h][0].name[0]=='w' || (strcmp(mt.m[h][0].name,"x0")==0) ){
                                    continue;
                                }
                                if(strcmp(mt.m[h][0].name,freeName[i+1])==0){
                                char *result = find(head, mt.m[h][0].name);
                                strcpy(mt.m[h][0].name, result);
                                break;
                                }
                            }                            
                        }
                    }
                }

            }
        }
        if(size_freeName>0){
            printIteration(mt);
        }
       

        for(int j=2;j<=mt.numCol-1;j++){
         //neu co ton tai c=0 thi so luong bien bi khuyet + 1    
            if((mt.m[0][j].coef==0) && (strcmp(mt.m[0][j].name,"x0")!=0)){
                khuyet+=1;
            }
        }
        //neu khong co bien nao bi khuyet, nghia la da co tu vung toi uu, ta ket luan Nghiem
        if( khuyet== 0){
            displayDistinctRoot(mt,count,test);
            return 0;
        }
        //neu co 3 bien khuyet tro len, ta ket luan bai toan khong gioi noi 
        if( khuyet >=3){
            printf("\nBai toan co vo so nghiem.");
            return 0;
        }
        //Neu co mot bien khuyet, tim khoang gioi han cua bien khuyet
        if (khuyet ==1){
            displayOneMissing(mt,count,test);    
            return 0;
        }
        //Neu co hai bien khuyet, tim he dieu kien
        if (khuyet ==2){
            displayTwoMissing(mt,count,test);
            return 0;
        }
    } 
    //co bien vao co bien ra nen thuc hien phep xoay 
    if (inputVar!=-1 && outputVar!=-1) {
        return 1;
    }
    //co bien vao khong co bien ra,mien chap nhan duoc khong gioi noi 
    if (inputVar!=-1 &&outputVar==-1) {
        printf("\nMien chap nhan duoc khong gioi noi.\n");
        if(test == 0){
        	printf("max z = + Inf \n");
        }else{
        	printf("min z = - Inf \n");
		}
        return 0;
    }
    return 0;
}

// Mot lan xoay
matrixVariable singleIteration(matrixVariable mt, int idx_input, int idx_output){
	float output_value = mt.m[idx_output][idx_input].coef; //Bien ra
	
	for(int i = 0; i<mt.numRow; i++){
		if(i!=idx_output){
			float temp = mt.m[i][idx_input].coef/output_value; 
		
			// Tinh toan lai he so tai hang idx_i
			for(int j = 1; j< (mt.numCol); j++){
				mt.m[i][j].coef -= temp*mt.m[idx_output][j].coef;
			}	
			// Bien tai vi tri bien vao da mat, ta xoa he so cua bien do
			for(int j = idx_input; j < (mt.numCol-1); j++){
				mt.m[i][j].coef = mt.m[i][j+1].coef;
				strcpy(mt.m[i][j].name, mt.m[i][j+1].name);
			}	
			// Them bien sau khi tinh toan
			mt.m[i][mt.numCol-1].coef = temp;
			strcpy(mt.m[i][mt.numCol - 1].name, mt.m[idx_output][0].name);	
		}				
	}	
	
	// Xet hang co bien ra	
	char temp[10];
	strcpy(temp, mt.m[idx_output][0].name); // Ten bien co so
	// Dua bien ra ra ngoai
	strcpy(mt.m[idx_output][0].name, mt.m[idx_output][idx_input].name);
	// Dua bien co so vao
	for(int j = idx_input; j < (mt.numCol-1); j++){
		mt.m[idx_output][j].coef = mt.m[idx_output][j+1].coef;
		strcpy(mt.m[idx_output][j].name, mt.m[idx_output][j+1].name);
	}	
	mt.m[idx_output][mt.numCol-1].coef = -1;
	strcpy(mt.m[idx_output][mt.numCol - 1].name, temp);
	// Tinh toan lai he so 
	for(int j = 1; j< mt.numCol; j++){
		mt.m[idx_output][j].coef /= -output_value;
	}	

	return mt;
}

//Phuong phap don hinh 
//Co in tu vung
void simplexAlgorithm(matrixVariable mt, int* count, int test,char freeName[10][3],int size_freeName,struct Node* head){
	if(count==0){
	    (*count)=0;
	}
	int idx_input;
	int idx_output;
	
	//In tu vung xuat phat 
	printIteration(mt);
	
	// Neu dieu kien dung co he so am o ham muc tieu thi tien hanh xoay don hinh
	do{
		idx_input =-1;
		idx_output=-1;
		simplexInputOutput(mt,&idx_input, &idx_output);
		printf("Input: %d\n",idx_input);
		printf("Output: %d\n",idx_output);
		if(idx_input == -1 || idx_output == -1){
			checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head);
			break;
		}	
		// Thuc hien mot lan xoay
		mt = singleIteration(mt, idx_input, idx_output);
		(*count)++;
		// In mot lan xoay
		printIteration(mt);
		
	}while(checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head)==1);
}

//Khong in tu vung
void simplexAlgorithmNoPrint(matrixVariable mt, int* count, int test,char freeName[10][3],int size_freeName,struct Node* head){
	if(count==0){
	    (*count)=0;
	}
	int idx_input;
	int idx_output;
	
	// Neu dieu kien dung co he so am o ham muc tieu thi tien hanh xoay don hinh
	do{
		idx_input =-1;
		idx_output=-1;
		simplexInputOutput(mt,&idx_input, &idx_output);
		if(idx_input == -1 || idx_output == -1){
			checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head);
			break;
		}	
		// Thuc hien mot lan xoay
		mt = singleIteration(mt, idx_input, idx_output);
		(*count)++;
		
	}while(checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head)==1);
}

//Tao tu vung xuat phat cho don hinh hai pha
matrixVariable createTwoPhase(int n,int m,float c[10],float A[10][10], float b[10],matrixVariable matrix){
	
	//So cot cua tu vung se bang so bien cong voi he so tu do cong voi cot z cong voi cot x0 (+3)
	matrix.numCol=3+n;
	
	//So hang cua tu vung se bang so rang buoc cong ham muc tieu (+1)
	matrix.numRow=1+m;
	
	for(int i=0;i<(matrix.numRow);i++){
		for(int j=0;j<(matrix.numCol);j++){
			//Xet cot dau tien
			if(j==0){
				//Tham so xuat phat cua cot dau tien la 1
				(matrix.m[i][0].coef)=1;
				//Dat ten cho cot dau tien
				if(i==0){
					//dong dau tien cua cot dau co ten bien la z
					strcpy(matrix.m[0][0].name,"E");
				} else{
					//Cac dong con lai co ten bien la w1,w2,w3,...
				     char var_name[3];
				     var_name[0] = 'w';
				     var_name[1] = (char)(i+48);
				     var_name[2]='\0';
					strcpy(matrix.m[i][0].name,var_name);
				}
			} else if(j==1){
				//Xet cot thu hai //cot he so tu do
				
				//cot he so tu do nen khong co name mac dinh la "NA"
				strcpy(matrix.m[i][1].name,"NA");
				if(i==0){
					//He so tu do cua ham muc tieu = 0
					matrix.m[0][1].coef=0;
				}else{
					//The cac he so tu do con lai lay du lieu tu mang b 
					matrix.m[i][1].coef=b[i-1];
				}
			}else if(j==matrix.numCol-1){
				//Xet cot cuoi cung - Cot x0
				strcpy(matrix.m[i][j].name,"x0");
				matrix.m[i][j].coef=1;
			}else{
				//Xet cac cot con lai
				
				//Cac cot co ten bien la x1,x2,x3,...
			    char var_name[3];
				var_name[0] = 'x';
				var_name[1] = (char)(j-1+48);
				var_name[2] = '\0';
				strcpy(matrix.m[i][j].name,var_name);
				
				if(i==0){
					//Cho tham so cua cac bien de cho deu bang 0 
					matrix.m[0][j].coef=0;
				}else{
					//Cac dong con lai lay du lieu tu ma tran A
					matrix.m[i][j].coef= - A[i-1][j-2];
				}
			}
		}
	}
	
	return matrix;
}

//Phuong phap hai pha
//Co in tu vung
void twophaseSimplexAlgorithm(matrixVariable matrix, int* count,int test,float c[],char freeName[10][3],int size_freeName,struct Node* head){
	(*count)=0;
	//Pha 1
	printf("\nPha 1:\n"); 
	
	//Bien vao la x0 
	int idx_input=matrix.numCol-1;
	
	//Bien ra la he so tu do am nhat 
	float min_output=0;
	int idx_output;
	for(int i=1;i<(matrix.numRow);i++){
		if(matrix.m[i][1].coef<min_output){
			min_output=matrix.m[i][1].coef;
			idx_output=i;
		}
	}
	
	printIteration(matrix);
	printf("Input: %d\n",idx_input);
	printf("Output: %d\n",idx_output);
		
	//Xoay tu vung xuat phat 
	matrix = singleIteration(matrix, idx_input, idx_output);
	printIteration(matrix);
	(*count)++;
	
	//Xoay cac tu vung tiep theo 
	do{
		idx_input=-1,idx_output=-1;
		simplexInputOutput(matrix, &idx_input, &idx_output);
		printf("Input: %d\n",idx_input);
		printf("Output: %d\n",idx_output);
		//Neu bien ra la x0 thi dung pha 1 hoac ket luan bai toan vo nghiem
		if(strcmp(matrix.m[idx_output][0].name,"x0")==0){
			//Xoay de chuyen x0 len ham muc tieu va kiem tra thuoc truong hop nao
			matrix = singleIteration(matrix, idx_input, idx_output);
			printIteration(matrix);
			(*count)++;
			idx_input=-1,idx_output=-1;
		    simplexInputOutput(matrix, &idx_input, &idx_output);
		    printf("Input: %d\n",idx_input);
		    printf("Output: %d\n",idx_output);
		    //Chon bien vao, bien ra moi 
			if(idx_input!=-1&&idx_output!=-1){
				//Neu van co bien vao, bien ra (tuc la khac -1)
				//Tiep tuc xoay 
				continue; 
			}else{
			//Xet cac bien khac x0
			for(int j=1;j<matrix.numCol;j++){	
				if(strcmp(matrix.m[0][j].name,"x0")!=0&&matrix.m[0][j].coef!=0){
					//Cac bien khac x0 co he so khac 0 (tuc ham muc tieu ton tai x0 va nhung bien khac)
					//Thi ket luan bai toan vo nghiem 
					printf("Bai toan vo nghiem.\n");
					return;
			   }
			}	
			//Neu ham muc tieu chi co bien x0 bai toan chuyen sang pha 2
			break;
		    }
		}
		else if(idx_input==-1){
			//Truong hop x0 khong quay lai ham muc tieu nhung khong co bien vao 
			printf("Bai toan vo nghiem.\n");
			return;
		}
		else{
		//Neu x0 khong phai bien ra thi tiep tuc xoay tu vung
			matrix = singleIteration(matrix, idx_input, idx_output);
			printIteration(matrix);
			(*count)++;
		}
	}while(checkInputOutput(matrix, idx_input,idx_output,*count,test,freeName,size_freeName,head)==1);
	
	//Pha 2
	
	printf("\nPha 2:\n"); 
	//Ta co numCol luc dau la 3+n (xem lai ham createTwoPhase) 
	int n=matrix.numCol - 3; //So bien

	char name[10][3]; //Tao mang chua cac ten bien 

	for(int i=0;i<n;i++){
		 name[i][0]='x';
		 name[i][1]=(char)(i+49);
		 name[i][2]='\0'; 
	}

	//Cho bien x0 o ham muc tieu va cac rang buoc bang 0 (Tuc xoa cot x0) 
	matrix.numCol--;

	int idx[10], a=0; //mang idx luu chi so cua nhung bien co so x //a la so bien cua mang idx
	for(int i=1;i<matrix.numRow;i++){
		//Xet cac bien co so co phai la bien x khong? 
		if(matrix.m[i][0].name[0]=='x'){
			//Neu co thi them chi so cua bien do vao mang idx 
			idx[a]=i;
			a++;
		}
	}
	
	//idx_c la chi so cua he so cac bien x tuong ung trong ham muc tieu luc dau 
	int idx_c;
	
	//Luu cac bien x bien nao la bien co so 
	//La bien co so chuyen thanh 1 
	//Khoi tao ban dau la 0
	int base[10]={0};
	
	//Vong lap chi xet nhung chi so la bien x
	for(int k=0;k<a;k++){
		//Vong lap xet tung chuoi trong mang ten bien da luu truoc do 
		for(int i=0;i<n;i++){
			//Xet nhung dong chi chua bien x //Bo qua nhung dong chua bien w
			//Tra ten bien dang xet voi mang ten bien name de biet chi so cua bien do tren ham muc tieu ban dau 
			if(matrix.m[idx[k]][0].name[1] == name[i][1]){
				idx_c=i;
				base[i]=1;
			}
		}
		//Xu ly ham muc tieu moi 
		//Cong cac bien x la bien co so
		for(int j=1;j<matrix.numCol;j++){
			matrix.m[0][j].coef+=(c[idx_c]*matrix.m[idx[k]][j].coef);
		}
	}
	
	//Cong cac bien x khong la bien co so
	if(a<n){
		for(int s=0;s<n;s++){
			if(base[s]==0){
				for(int w=2;w<matrix.numCol;w++){
					if(strcmp(name[s],matrix.m[0][w].name)==0){
							matrix.m[0][w].coef+=c[s];
					}
				}
			}
		}
	}
	
	//Xu ly bai toan nhu bai toan don hinh binh thuong	
	simplexAlgorithm(matrix, count, test,freeName,size_freeName,head);	
}                

//Khong in ra tu vung
void twophaseSimplexAlgorithmNoPrint(matrixVariable matrix, int* count,int test,float c[],char freeName[10][3],int size_freeName,struct Node* head){
	(*count)=0;
	//Pha 1
	
	//Bien vao la x0 
	int idx_input=matrix.numCol-1;
	
	//Bien ra la he so tu do am nhat 
	float min_output=0;
	int idx_output;
	for(int i=1;i<(matrix.numRow);i++){
		if(matrix.m[i][1].coef<min_output){
			min_output=matrix.m[i][1].coef;
			idx_output=i;
		}
	}
		
	//Xoay tu vung xuat phat 
	matrix = singleIteration(matrix, idx_input, idx_output);
	(*count)++;
	
	//Xoay cac tu vung tiep theo 
	do{
		idx_input=-1,idx_output=-1;
		simplexInputOutput(matrix, &idx_input, &idx_output);
		//Neu bien ra la x0 thi dung pha 1 hoac ket luan bai toan vo nghiem
		if(strcmp(matrix.m[idx_output][0].name,"x0")==0){
			//Xoay de chuyen x0 len ham muc tieu va kiem tra thuoc truong hop nao
			matrix = singleIteration(matrix, idx_input, idx_output);
			(*count)++;
			idx_input=-1,idx_output=-1;
		    simplexInputOutput(matrix, &idx_input, &idx_output);
		    //Chon bien vao, bien ra moi 
			if(idx_input!=-1&&idx_output!=-1){
				//Neu van co bien vao, bien ra (tuc la khac -1)
				//Tiep tuc xoay 
				continue; 
			}else{
			//Xet cac bien khac x0
			for(int j=1;j<matrix.numCol;j++){	
				if(strcmp(matrix.m[0][j].name,"x0")!=0&&matrix.m[0][j].coef!=0){
					//Cac bien khac x0 co he so khac 0 (tuc ham muc tieu ton tai x0 va nhung bien khac)
					//Thi ket luan bai toan vo nghiem 
					printf("Bai toan vo nghiem.\n");
					return;
			   }
			}	
			//Neu ham muc tieu chi co bien x0 bai toan chuyen sang pha 2
			break;
		    }
		}
		else if(idx_input==-1){
			//Truong hop x0 khong quay lai ham muc tieu nhung khong co bien vao 
			printf("Bai toan vo nghiem.\n");
			return;
		}
		else{
		//Neu x0 khong phai bien ra thi tiep tuc xoay tu vung
			matrix = singleIteration(matrix, idx_input, idx_output);
			(*count)++;
		}
	}while(checkInputOutput(matrix, idx_input,idx_output,*count,test,freeName,size_freeName,head)==1);
	
	//Pha 2
	
	//Ta co numCol luc dau la 3+n (xem lai ham createTwoPhase) 
	int n=matrix.numCol - 3; //So bien

	char name[10][3]; //Tao mang chua cac ten bien 

	for(int i=0;i<n;i++){
		 name[i][0]='x';
		 name[i][1]=(char)(i+49);
		 name[i][2]='\0'; 
	}

	//Cho bien x0 o ham muc tieu va cac rang buoc bang 0 (Tuc xoa cot x0) 
	matrix.numCol--;

	int idx[10], a=0; //mang idx luu chi so cua nhung bien co so x //a la so bien cua mang idx
	for(int i=1;i<matrix.numRow;i++){
		//Xet cac bien co so co phai la bien x khong? 
		if(matrix.m[i][0].name[0]=='x'){
			//Neu co thi them chi so cua bien do vao mang idx 
			idx[a]=i;
			a++;
		}
	}
	
	//idx_c la chi so cua he so cac bien x tuong ung trong ham muc tieu luc dau 
	int idx_c;
	
	//Luu cac bien x bien nao la bien co so 
	//La bien co so chuyen thanh 1 
	//Khoi tao ban dau la 0
	int base[10]={0};
	
	//Vong lap chi xet nhung chi so la bien x
	for(int k=0;k<a;k++){
		//Vong lap xet tung chuoi trong mang ten bien da luu truoc do 
		for(int i=0;i<n;i++){
			//Xet nhung dong chi chua bien x //Bo qua nhung dong chua bien w
			//Tra ten bien dang xet voi mang ten bien name de biet chi so cua bien do tren ham muc tieu ban dau 
			if(matrix.m[idx[k]][0].name[1] == name[i][1]){
				idx_c=i;
			}
		}
		//Xu ly ham muc tieu moi 
		//Cong cac bien x la bien co so
		for(int j=1;j<matrix.numCol;j++){
			matrix.m[0][j].coef+=(c[idx_c]*matrix.m[idx[k]][j].coef);
		}
	}
	
	//Cong cac bien x khong la bien co so
	if(a<n){
		for(int s=0;s<n;s++){
			if(base[s]==0){
				for(int w=2;w<matrix.numCol;w++){
					if(strcmp(name[s],matrix.m[0][w].name)==0){
							matrix.m[0][w].coef+=c[s];
					}
				}
			}
		}
	}
	
	//Xu ly bai toan nhu bai toan don hinh binh thuong	
	simplexAlgorithmNoPrint(matrix, count, test,freeName,size_freeName,head);	
}                

//Phuong phap Bland
//Co in tu vung
void blandAlgorithm(matrixVariable mt, int test,int *count,arrayPriority pr,char freeName[10][3],int size_freeName,struct Node* head){
	pr=priorityOrder(mt, pr);
	(*count)=0;
	int idx_input;
	int idx_output;
	
	//In tu vung xuat phat 
	printIteration(mt);
	
	// Neu dieu kien dung co he so am o ham muc tieu thi tien hanh xoay 
	do{
		idx_input =-1;
		idx_output=-1;
		blandInputOutput(mt,&idx_input, &idx_output,pr);
		printf("Input: %d\n",idx_input);
		printf("Output: %d\n",idx_output);
		if(idx_input == -1 || idx_output == -1){
			checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head);
			break;
		}	
		// Thuc hien mot lan xoay
		mt = singleIteration(mt, idx_input, idx_output);
		(*count)++;
		// In mot lan xoay
		printIteration(mt);
		
	}while(checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head)==1);
}

//Khong in tu vung
void blandAlgorithmNoPrint(matrixVariable mt, int test,int *count,arrayPriority pr,char freeName[10][3],int size_freeName,struct Node* head){
	pr=priorityOrder(mt, pr);
	(*count)=0;
	int idx_input;
	int idx_output;
	
	// Neu dieu kien dung co he so am o ham muc tieu thi tien hanh xoay 
	do{
		idx_input =-1;
		idx_output=-1;
		blandInputOutput(mt,&idx_input, &idx_output,pr);
		if(idx_input == -1 || idx_output == -1){
			checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head);
			break;
		}	
		// Thuc hien mot lan xoay
		mt = singleIteration(mt, idx_input, idx_output);
		(*count)++;
	}while(checkInputOutput(mt, idx_input, idx_output, *count, test,freeName,size_freeName,head)==1);
}

void chooseMethod(matrixVariable mt,float b[],int m,int count,int test,float c[],arrayPriority pr,int n,float A[10][10],int choose,char freeName[10][3],int size_freeName,struct Node* head){
    //bien kiem tra gia tri cua b 
    //neu co b am check =-1 va xoay bang pp don hinh 2 pha 
    //neu co b=0  thi check=1 va xoay bang phuong phap bland
    //truong hop con lai xoay bang phuong phap don hinh 
    int check=0;
    for(int i=0;i<m;i++){
        if(b[i]<0){
            check=-1;
            break;
        }
        if(b[i]==0){
            check=1;
            break;
        }
    }
    
    if(check ==-1){
    	system("cls");
        mt=createTwoPhase( n,m,c,A, b,mt);
        if(choose==3){
            twophaseSimplexAlgorithm(mt,&count,test,c,freeName,size_freeName,head);
        }else{
        	twophaseSimplexAlgorithmNoPrint(mt,&count,test,c,freeName,size_freeName,head);
		}
    }else{
        if(check == 1){
        	system("cls");
        	if(choose==3){
			    blandAlgorithm(mt,test,&count,pr,freeName,size_freeName,head);       
			}else{
				blandAlgorithmNoPrint(mt,test,&count,pr,freeName,size_freeName,head); 
			}
        }else {
            int k=0;
            printf("\nChon phuong phap giai cua bai toan (Chi nhap 1 hoac 2)\n1.Phuong phap don hinh\n2.Phuong phap xoay Bland\n");
        	scanf("%d", &k);
        	system("cls");
        	if(k==1){
        		if(choose==3){
				    simplexAlgorithm(mt, &count, test,freeName,size_freeName,head);
				}else{
					simplexAlgorithmNoPrint(mt, &count, test,freeName,size_freeName,head);
                }
        	}
            if(k==2){
                if(choose==3){
			        blandAlgorithm(mt,test,&count,pr,freeName,size_freeName,head);       
			    }else{
			     	blandAlgorithmNoPrint(mt,test,&count,pr,freeName,size_freeName,head); 
		    	}
            }
        }
    }
    
}

int main()
{
	int n; // So bien
	int m; // So rang buoc
	int test; //ma hoa min/max (min = 1, max = 0)
	float c[10]; //he so ham muc tieu
	float A[10][10]; //he so cac bien o cac rang buoc
	float b[10]; //b o cac rang buoc
	int sign[5]; // dau o cac rang buoc (0 la "=",1 la "<=", 2 la ">=")
	int tt[10]; //bien tu do
	matrixVariable matrix; //tu vung 
	arrayPriority pr; //Thu tu uu tien cua cac bien trong tu vung
	int count; //Bien dem so buoc xoay  
	char freeName[10][3];//mảng chua ten cac bien tu do 
	int size_freeName;
    struct Node* head = NULL;//struc chua ten cua bien tu do sau khi xu ly,value la ten bien ban dau,key la ten bien luc sau

	int idx_input ,idx_output;
	
	int choose;
	do
	{
		Menu();
		printf("\nNhap lua chon: ");
		scanf("%d", &choose);
		
		switch (choose)
		{
		case 1:
		    system("cls");
			input(&n,&m,c,A,b,sign,&test,tt);
			makeList(&head,tt,n,freeName,&size_freeName);
			transStandard(&n,&m,c,A,b,sign,tt);

			system("cls");
			printf("\nDang chuan cua bai toan:\n");
			printStandard(n,m,c,A,b,sign,test,tt);

			Press();
			break;
		case 2:
			matrix=createMatrix(n,m,c,A,b,matrix);
           chooseMethod(matrix,b,m,count,test,c,pr,n,A,choose,freeName,size_freeName,head);
			Press();
			break;
		case 3:
			matrix=createMatrix(n,m,c,A,b,matrix);
            chooseMethod(matrix,b,m,count,test,c,pr,n,A,choose,freeName,size_freeName,head);
			Press();
			break;
		case 0:
			printf("\nKet thuc.\n");
			break;
		default:
			printf("\nNhap lai.");
		}

		
	}while(choose);
	
	return 0;
	
}


