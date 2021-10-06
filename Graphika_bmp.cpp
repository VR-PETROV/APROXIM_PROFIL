#include "bibl_c.cpp"
#include <io.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ����������� ������������ ��� �������������� ���� "unsigned long" � "unsigned char" � �������.
//

union
{
	unsigned long ul;
	unsigned char uch[4];

} perevod4;
	

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// 	������� �������� ����� ����������� � ������� BMP		//////////////
//
//
//	������� ��������� :	
//				
//		Xmax	- ������ ����������� � �������� �� �����������
//		Ymax	- ������ ����������� � �������� �� ���������
//		cs	- ���� ���� ����� ������������
//		cz	- ���� ���� ������� ������������	
//		ck	- ���� ���� ������� ������������
//
//
//	�������� ��������� :
//
//		** buf1	- ��������� �� ������� ������ � ������� ��������� �����������
//
//	������������ �������� :
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//


int create_bmp( unsigned long Xmax, unsigned long Ymax, unsigned char cs, unsigned char cz, unsigned char ck, unsigned char * * buf1 )
{

unsigned char * buf;	// ��������� �� ������� ������ � ������� ������� ����� BMP-�����
unsigned long i;		// ������� �����
unsigned long kol_dobaw;	// ���������� ���������� ���� � ������ �����������.
unsigned long razmer_izobr;	// ������ ������������ ����������� � ������
unsigned long dlina_file;	// ������ ���������� ������� ������ ��� �������� �����������
unsigned long sdw_obl_dan;	// �������� ������� ������ ������������ ������ �����
unsigned long dlina_inf_zagol;	// ����� ��������������� ��������� BMP �����
unsigned long X,Y;		// ���������� ������� �����
unsigned long poz;		// ��������� �� ������� � ������ BMP-�����


// ���������� ���������� ���������� ���� � ������ �����������.
kol_dobaw = (unsigned long) fmod( (double) Xmax, 4.00);


// ������ �������� ������� ������ ������������ ������ �����
sdw_obl_dan = 54;


// ������ ����� ��������������� ��������� BMP �����
dlina_inf_zagol = 40;


// ���������� ������ ������������ ����������� � ������.
razmer_izobr = (Xmax*3+kol_dobaw)*Ymax;


// ���������� ������ ����� �����������.
dlina_file = razmer_izobr + sdw_obl_dan;


// ��������� ������� ������ ��� �������� ������ ����� ����������� � ������� BMP.
buf = (unsigned char *) malloc(dlina_file);


// ���� ��������� ������� ��� ��������� ������� ������ ��� �������� ������ ����� ����������� ����� 
// ����� �� ������� � ��������� ���� ������.
if (buf==NULL) return 0;


// ��������� ���������� ������� ������ "0".
memset(buf, 0, dlina_file);


// �������� � ������ ��� ����� ������ ����� ����������� "BM".
buf[0] = 'B';
buf[1] = 'M';


// ������� � ������� � 2 �������� 4 ����� ��������������� ������ ����� ����������� � ������.
perevod4.ul = dlina_file;
for (i=0; i<4; i++) buf[i+2]=perevod4.uch[i];


// ������� � ������� � 10 �������� 4 ����� ��������������� �������� ������� ������ ������������ ������ ����� = 54
perevod4.ul = sdw_obl_dan;
for (i=0; i<4; i++) buf[i+10]=perevod4.uch[i];


// ������� � ������� � 14 �������� 4 ����� ��������������� ����� ��������������� ��������� = 40
perevod4.ul = dlina_inf_zagol;
for (i=0; i<4; i++) buf[i+14]=perevod4.uch[i];


// ������� � ������� � 18 �������� 4 ����� ��������������� ����� ����������� �� ����������� � ��������.
perevod4.ul = Xmax;
for (i=0; i<4; i++) buf[i+18]=perevod4.uch[i];


// ������� � ������� � 22 �������� 4 ����� ��������������� ����� ����������� �� ������������� � ��������.
perevod4.ul = Ymax;
for (i=0; i<4; i++) buf[i+22]=perevod4.uch[i];


// ������� � ������� � 26 �������� 2 ����� ��������������� ���������� �������� ���������� = 1
perevod4.ul = 1;
for (i=0; i<2; i++) buf[i+26]=perevod4.uch[i];


// ������� � ������� � 28 �������� 2 ����� ��������������� ���������� ��� �� ������� = 24
perevod4.ul = 24;
for (i=0; i<2; i++) buf[i+28]=perevod4.uch[i];


// ������� � ������� � 30 �������� 4 ����� ��������������� ��� ������ ������ = 0 (��� ������).
perevod4.ul = 0;
for (i=0; i<4; i++) buf[i+30]=perevod4.uch[i];


// ������� � ������� � 34 �������� 4 ����� ��������������� ������ ������������ ����������� � ������.
perevod4.ul = razmer_izobr;
for (i=0; i<4; i++) buf[i+34]=perevod4.uch[i];


// ������� � ������� � 38 �������� 4 ����� ��������������� ���������� �� ����������� = 0
perevod4.ul = 0;
for (i=0; i<4; i++) buf[i+38]=perevod4.uch[i];


// ������� � ������� � 42 �������� 4 ����� ��������������� ���������� �� ���������.
perevod4.ul = 0;
for (i=0; i<4; i++) buf[i+42]=perevod4.uch[i];


// ��������� ���� ����������� ������ (cs,  cz, ck)
for(Y=0; Y<Ymax; Y++)
{	
	for ( X=0; X< Xmax; X++)
	{
		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz=sdw_obl_dan+(Xmax*3+kol_dobaw)*Y+X*3;

		// �������� � ����� ���� ����� �����.
		buf[poz]     = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}
}




// �������� ���������� ��������� ����� ������ � ������� ������� ���� �����������
* buf1=buf;


// ����� �� ������� � ��������� ���� ��������� ����������.
return 1;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// 	������� �������� ����� ����������� � ������� BMP		//////////////
//
//
//	������� ��������� :	
//
//		file_name - ��� ����� � ������� ��������� ����������� � ������� BMP
//
//
//	�������� ��������� :	
//
//	     	 ** buf1 - ��������� �� ������� ������ � ������� ��������� �����������
//
//
//	������������ �������� :		
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������		
//		


int open_bmp( char * file_name, unsigned char * * buf1 )

{

int f;			// �������� ���������� 
unsigned long dlina_file;	// ����� ����� � ������	
unsigned char * buf;	// ��������� �� ������� ������ � ������� ������� ����� BMP-�����


// ������� ��������� ���� �����������
f=open(file_name, O_WRONLY | O_BINARY, 0);

// ���� ���� ������� �� ������� ����� ����� �� ������� � ��������� ���� ������.
if (f == -1) return 0;


// ���������� ������ ����� �����������
lseek(f,0L,2);
dlina_file = tell(f);


// �������� ������� ������ (�����) ��� �������� ����� �����������
buf = (unsigned char *) malloc(dlina_file); 

if (buf == NULL) 
{
	// ������ ��� ��������� ������ ��� �������� ����� �����������

	// ������� ����� �������� ����
	close(f);	

	// ����� �� ������� � ��������� ���� ������.
	return 0;
}


// ������� ���� ����������� � �����
lseek(f,0L,0);
read(f,buf,dlina_file);


// ������� ����� �������� ����
close(f);	


// �������� ���������� ��������� ����� ������ � ������� ������� ���� �����������
* buf1=buf;

// ����� �� ������� � ��������� �������� �������� ����������.
return 1;


}


//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// 	������� ���������� ����� ����������� � ������� BMP		//////////////
//
//
//	������� ��������� :	
//
//		file_name - ��� ����� � ������� ����������� ����������� � ������� BMP
//		buf 	  - ��������� �� ������� ������ � ������� ��������� �����������	
//
//	������������ �������� :		
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������		
//		


int save_bmp( char * file_name, unsigned char * buf )

{

int f;				// �������� ���������� 
unsigned long dlina_file;	// ����� ����� � ������	
unsigned long i;		// ������� �����


// ������� ���� ��� ������ �����������.
f=open(file_name, O_CREAT | O_WRONLY | O_BINARY, S_IWRITE );




// ���� ���� ������� �� ������� ����� ����� �� ������� � ��������� ���� ������.
if (f == -1) return 0;


// ������� ����� �����
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+2];
dlina_file = perevod4.ul;


// ���������� ������ �������� � ����.
write(f, buf, dlina_file);


// ������� ����
close(f);


// ���������� �����
free(buf);


// ����� �� ������� � ��������� �������� �������� ����������.
return 1;


}


//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// 		������� ��������� �����					//////////////
//
//
//	������� ��������� :
//
//		buf 	- ��������� �� ������� ������ � ������� ��������� �����������
//		X	- ���������� x �����
//		Y	- ���������� y �����
//		cs	- ���� ����� ����� ������������
//		cz	- ���� ����� ������� ������������
//		ck	- ���� ����� ������� ������������
//
//
//	������������ �������� :
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//


int point( unsigned char * buf, long X, long Y, unsigned char cs, unsigned char cz, unsigned char ck )
{


unsigned long i;		// ������� �����
unsigned long sdw_obl_dan;	// ����� ������� ������ ������������ ������ �����
unsigned long poz;		// ������� � ����� ������� � ������� ���� ���������� ���� �����
unsigned long kol_dobaw;	// ���������� ���������� ���� � ������ �����������
int code_ret;		// ��� ������������ ��� ���������� �������

long Xmax;		// ������ ����������� �� �����������
long Ymax;		// ������ ����������� �� ���������


// ������� ����� ������� ������ ������������ ������ ������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+10];
sdw_obl_dan=perevod4.ul;


// ������� ������ ����������� �� �����������
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+18];
Xmax = (long) perevod4.ul;


// ������� ������ ����������� �� ���������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+22];
Ymax= (long) perevod4.ul;


// ���������� ���������� ���������� ���� � ������ �����������
kol_dobaw = (unsigned long) fmod( (double) Xmax, 4.00);	


// �������������� ���������� Y
Y = Ymax-Y;


if ( (0<=X) && (X<Xmax) && (0<=Ymax) && (Y<Ymax))
{
	// ����� � ������������ (X,Y) �������� � ���� �����������

	// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
	poz=sdw_obl_dan+((long)Xmax*3+kol_dobaw)*Y+X*3;

	// �������� � ����� ���� ����� �����.
	buf[poz]   = cs;	
	buf[poz+1] = cz;
	buf[poz+2] = ck;

	// ���������� ��� �������� ����������.
	code_ret = 1;
}
else
{
	// ����� � ������������ (X,Y) �� �������� � ���� �����������
	// ���������� ��� ���������� ����������.
	code_ret = 0;
}


// ����� �� ������� � ��������� ���� ����������.
return code_ret;


}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// 		������� ��������� ������				/////////////
//
//
//	������� ��������� :
//
//		buf 	- ��������� �� ������� ������ � ������� ��������� �����������
//		X1	- ���������� x ��������� ����� ������
//		Y1	- ���������� y ��������� ����� ������
//		X2	- ���������� x �������� ����� ������
//		Y2	- ���������� y �������� ����� ������
//		cs	- ���� ������ ����� ������������
//		cz	- ���� ������ ������� ������������
//		ck	- ���� ������ ������� ������������
//
//
//	������������ �������� :
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//


int line( unsigned char * buf, long X1, long Y1, long X2, long Y2, unsigned char cs, unsigned char cz, unsigned char ck )
{

unsigned long i;		// ������� �����
unsigned long sdw_obl_dan;	// ����� ������� ������ ������������ ������ �����
unsigned long kol_dobaw;	// ���������� ���������� ���� � ������ �����������
unsigned long poz;		// ������� � ����� ������� � ������� ������������ ������� ����� �����������
double k;			// ����������� ������� ������

long X,Y;		// ���������� ����� ������������� �� ������
long Xp,Yp;	// ��������������� ����������
long Xmax;	// ������ ����������� �� �����������
long Ymax;	// ������ ����������� �� ���������


// ������� ����� ������� ������ ������������ ������ ������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+10];
sdw_obl_dan=perevod4.ul;


// ������� ������ ����������� �� �����������
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+18];
Xmax= (long) perevod4.ul;


// ������� ������ ����������� �� ���������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+22];
Ymax=(long) perevod4.ul;


// ���������� ���������� ���������� ���� � ������ �����������
kol_dobaw = (unsigned long) fmod( (double) Xmax, 4.00);


// �������������� Y1 � Y2
Y1 = Ymax - Y1;
Y2 = Ymax - Y2;


if (X2!=X1)
{
	//  ���������� X ��������� � �������� ����� �� ���������

	if ( fabs(((double)X2)-((double)X1)) >= fabs(((double)Y2)-((double)Y1)) )
	{
		//  | X2-X1 | >= | Y2-Y1 |

		if ( X2<X1)
		{
			// �������� ������� ��������� � �������� ����� �����
			Xp = X2;
			Yp = Y2;
			X2 = X1;
			Y2 = Y1;
			X1 = Xp;
			Y1 = Yp;
		}

		// ���������� ����������� ������� ������
		k = (((double)Y2)-((double)Y1))/(((double)X2)-((double)X1));

		// ������� � ����� ���� ����� ����� �� ��� � � �� ���������
		for (X=X1; X<=X2; X++)
		{
			// ���������� ���������� Y ��������� ����� ������
			Y = (long)(k * ((double)X-(double)X1))+((double)Y1);

			if ( (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
			{
				// ����� � ������������ (X,Y) �������� � ���� �����������

				// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
				poz=sdw_obl_dan+( (unsigned long)Xmax*3+kol_dobaw)*Y+X*3;

				// �������� � ����� ���� ����� �����.
				buf[poz]   = cs;
				buf[poz+1] = cz;
				buf[poz+2] = ck;
			}
		}
	}
	else
	{
		//  | X2-X1 | < | Y2-Y1 |

		if ( Y2<Y1)
		{
			// �������� ������� ��������� � �������� ����� �����
			Xp = X2;
			Yp = Y2;
			X2 = X1;
			Y2 = Y1;
			X1 = Xp;
			Y1 = Yp;
		}

		// ���������� ����������� ������� ������
		k = (((double)X2)-((double)X1))/(((double)Y2)-((double)Y1));

		// ������� � ����� ���� ����� ����� �� ��� � � �� ���������
		for (Y=Y1; Y<=Y2; Y++)
		{
			// ���������� ���������� X ��������� ����� ������
			X = (long)(k * ((double)Y-(double)Y1))+((double)X1);

			if (  (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
			{
				// ����� � ������������ (X,Y) �������� � ���� �����������

				// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
				poz=sdw_obl_dan+((unsigned long)Xmax*3+kol_dobaw)*Y+X*3;

				// �������� � ����� ���� ����� �����.
				buf[poz]   = cs;
				buf[poz+1] = cz;
				buf[poz+2] = ck;
			}
		}
	}
}
else
{
	// ���������� X ��������� � �������� ����� ���������

	if ( Y2<Y1)
	{
		// �������� ������� ��������� � �������� ����� �����
		Yp = Y2;
		Y2 = Y1;
		Y1 = Yp;
	}

	// ������ ���������� X ������������ ������ �����
	X=X1;

	// ������� � ����� ���� ����� ����� � �� ���������
	for (Y=Y1; Y<=Y2; Y++)
	{
		if (  (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
		{
			// ����� � ������������ (X,Y) �������� � ���� �����������

			// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
			poz=sdw_obl_dan+((unsigned long)Xmax*3+kol_dobaw)*Y+X*3;

			// �������� � ����� ���� ����� �����.
			buf[poz]   = cs;
			buf[poz+1] = cz;
			buf[poz+2] = ck;
		}
	}
}



// ����� �� ������� � ��������� ���� �������� ����������
return 1;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// 		������� ��������� ����������				/////////////
//
//
//	������� ��������� :
//
//		buf 	- ��������� �� ������� ������ � ������� ��������� �����������
//		Xc	- ���������� X ������ ����������
//		Yc	- ���������� Y ������ ����������
//		R	- ������ ����������
//		cs	- ���� ���������� ����� ������������
//		cz	- ���� ���������� ������� ������������
//		ck	- ���� ���������� ������� ������������
//
//
//	������������ �������� :
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//


int krug( unsigned char * buf,  long Xc, long Yc,  long R, unsigned char cs, unsigned char cz, unsigned char ck )
{


unsigned long i;		// ������� �����
unsigned long sdw_obl_dan;	// ����� ������� ������ ������������ ������ �����
unsigned long kol_dobaw;	// ���������� ���������� ���� � ������ �����������
unsigned long poz;		// ������� ������� � ������

long X,Y;		// ���������� X,Y ����� ����������
long X1_okr;	// ���������� � ����� ����� ��������� ���������� ( ��� ��������� ����� ���  X )
long X2_okr;	// ���������� � ������ ����� ��������� ���������� ( ��� ��������� ����� ���  X )
long Y1_okr;	// ���������� Y ������ ����� ��������� ���������� ( ��� ��������� ����� ���  Y )
long Y2_okr;	// ���������� Y ������� ����� ��������� ���������� ( ��� ��������� ����� ���  Y )
long Xmax;	// ������ ����������� �� �����������
long Ymax;	// ������ ����������� �� ���������



// ������� ����� ������� ������ ������������ ������ ������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+10];
sdw_obl_dan=perevod4.ul;

// ������� ������ ����������� �� �����������
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+18];
Xmax= (long) perevod4.ul;

// ������� ������ ����������� �� ���������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+22];
Ymax= (long) perevod4.ul;

// ���������� ���������� ���������� ���� � ������ �����������
kol_dobaw = (unsigned long) fmod( (double) Xmax, 4.00);

// �������������� Yc
Yc = Ymax - Yc;



// ���������� ���������� X ����� ����� ��������� ����������
X1_okr = Xc - (long) ((double) R * 0.7071067811)  ;

// ���������� ����������  X ������ ����� ��������� ����������
X2_okr = Xc + (long) ((double) R * 0.7071067811)  ;

// ��������� ��������� ���������� ����� ��� X
for (X=X1_okr; X<=X2_okr; X++)
{
	// ���������� ���������� Y �������� ���������
	Y = (long) ((double)Yc+sqrt(sqr((double)R)-sqr((double)X-(double)Xc)));

	if (  (0<=X) &&  (X<Xmax) && (0<=Y) && (Y<Ymax) )
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)Y)+((unsigned long)X)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}

	// ���������� ���������� Y ������� ���������
	Y = (long) ((double)Yc-sqrt(sqr((double)R)-sqr((double)X-(double)Xc)));

	if ( (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)Y)+((unsigned long)X)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}
}


// ���������� ���������� Y ������ ����� ����������
Y1_okr = Yc - (long) ((double) R * 0.7071067811)  ;

// ���������� ����������  Y ������� ����� ����������
Y2_okr = Yc + (long) ((double) R * 0.7071067811)  ;

// ��������� ��������� ���������� ����� ��� Y
for (Y=Y1_okr; Y<=Y2_okr; Y++)
{
	// ���������� ���������� X ������� ���������
	X = (long) ((double)Xc+sqrt(sqr((double)R)-sqr((double)Y-(double)Yc)));

	if ( (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)Y)+((unsigned long)X)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}

	// ���������� ���������� X ������ ���������
	X = (long) ((double)Xc-sqrt(sqr((double)R)-sqr((double)Y-(double)Yc)));

	if ( (0<=X) && (X<Xmax) && (0<=Y) && (Y<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)Y)+((unsigned long)X)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}
}



// ����� �� ������� � ��������� ���� ��������� ����������
return 1;


}


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////// 			������� ��������� �������				/////////////
//
//
//	������� ��������� :
//
//		buf 	- ��������� �� ������� ������ � ������� ��������� �����������
//		Xc	- ���������� x ������ �������
//		Yc	- ���������� y ������ �������
//		a	- ����� ������� ������� �������
//		b	- ����� ������� ������� �������
//	alfa_gradus	- ���� �������� ������� � ��������
//		cs	- ���� ������� ����� ������������
//		cz	- ���� ������� ������� ������������
//		ck	- ���� ������� ������� ������������
//
//
//	������������ �������� :
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//

int ellips( unsigned char * buf,  long Xc,  long Yc,  long a,  long b,  double alfa_gradus,  unsigned char cs, unsigned char cz, unsigned char ck )

{

double pi=3.14159;		// ����� ��

unsigned long i;		// ������� �����
unsigned long sdw_obl_dan;	// ����� ������� ������ ������������ ������ �����
unsigned long kol_dobaw;	// ���������� ���������� ���� � ������ �����������
unsigned long poz;		// ������� ������� � ������

long X_lev;		// ���������� � ����� ������� ������� �������� ����� ��� �
long X_prav;		// ���������� � ������ ������� ������� �������� ����� ��� �

long Y_nig;		// ���������� Y ������ ������� ������� ��������� ����� ��� Y
long Y_werh;		// ���������� Y ������� ������� ������� ��������� ����� ��� Y

long X,Y;			// ���������� X,Y ����� �������
long Xmax;		// ������ ����������� �� �����������
long Ymax;		// ������ ����������� �� ���������
long XX, YY;		// ���������� X,Y ����� �������, ����� ��������

double alfa_radian;		// ���� �������� ������� � ��������
double a2_plus_b2;	// ��������������� ����������
double Diskrim;		// ��������������� ����������
double Xp1;		// ���������� "�" ����� �������� ������� ����� �������. ������� � 1



if (a == b)
{
	// ������� ������� �����.

	// ����� �� ������� � ��������� ���� ���������� ����������
	return 0;
}

// ������� ����� ������� ������ ������������ ������ ������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+10];
sdw_obl_dan=perevod4.ul;

// ������� ������ ����������� �� �����������
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+18];
Xmax = (long) perevod4.ul;

// ������� ������ ����������� �� ���������.
for (i=0; i<4; i++) perevod4.uch[i]=buf[i+22];
Ymax = (long) perevod4.ul;

// ���������� ���������� ���������� ���� � ������ �����������
kol_dobaw = (unsigned long) fmod( (double) Xmax, 4.00);

// �������������� Yc
Yc = Ymax - Yc;

// ������� ���� �������� ������� �� �������� � �������
alfa_radian =  alfa_gradus * pi/180;

// ���������� ���������� "X" ����� �������� ������� ����� ������� (��� ����������� ����� 1).
a2_plus_b2 = sqr( (double) a) + sqr( (double) b);
Diskrim = sqr(2*(double)Xc*a2_plus_b2) - 4*a2_plus_b2*(a2_plus_b2*sqr((double)Xc) - (double) a*a*a*a);

if (Diskrim < 0)
{
	// ���� ������������ ������������� ����� ����� �� ������� � ��������� ���� ������.
	return 0;
}

Xp1 =  (2*(double)Xc*a2_plus_b2-sqrt(Diskrim)) / (2*a2_plus_b2);

// ���������� ����� ������� ������� ��������� ����� ��� �
X_lev = Xp1;

// ���������� ������ ������� ������� ��������� ����� ��� �
X_prav = Xc + labs(Xc-Xp1)+1;


// ��������� ������� ������� ����� ��� �

for(X=X_lev; X<=X_prav;  X++)
{
	// ���������� ���������� Y ������� ����� �������
	Y = (long) Yc + b * sqrt(1-sqr(X-Xc)/sqr(a));

	// ������� ������� ������ ������ ������ �� ���� "alfa_radian"
	XX = (long) (X-Xc)*cos(alfa_radian)  -  (Y-Yc)*sin(alfa_radian) + Xc;
	YY = (long) (X-Xc)*sin(alfa_radian)  + (Y-Yc)*cos(alfa_radian) + Yc;

	if ((0<=XX) &&  (XX<Xmax) &&  (0<=YY) && (YY<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)YY)+((unsigned long)XX)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}

	// ���������� ���������� Y ������ ����� �������
	Y = (long) Yc - b * sqrt(1-sqr(X-Xc)/sqr(a));

	// ������� ������� ������ ������ ������ �� ���� "alfa_radian"
	XX = (long) (X-Xc)*cos(alfa_radian)  - (Y-Yc)*sin(alfa_radian) + Xc;
	YY = (long) (X-Xc)*sin(alfa_radian)  + (Y-Yc)*cos(alfa_radian) + Yc;

	if ((0<=XX) &&  (XX<Xmax) &&  (0<=YY) && (YY<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)YY)+((unsigned long)XX)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}
}


// ���������� ������ ������� ������� ��������� ����� ��� Y
Y_nig =	 (long) Yc - b * sqrt(1-sqr(X_lev-Xc)/sqr(a));

// ���������� ������� ������� ������� ��������� ����� ��� Y
Y_werh =  (long) Yc + b * sqrt(1-sqr(X_lev-Xc)/sqr(a));


// ��������� ������� ������� ����� ��� Y

for(Y=Y_nig; Y<=Y_werh; Y++)
{
	// ���������� ���������� X ����� ����� �������
	X = (long) Xc - a * sqrt(1-sqr(Y-Yc)/sqr(b));

	// ������� ������� ������ ������ ������ �� ���� "alfa_radian"
	XX = (long) (X-Xc)*cos(alfa_radian)  -  (Y-Yc)*sin(alfa_radian) + Xc;
	YY = (long) (X-Xc)*sin(alfa_radian)  + (Y-Yc)*cos(alfa_radian) + Yc;

	if ((0<=XX) &&  (XX<Xmax) &&  (0<=YY) && (YY<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)YY)+((unsigned long)XX)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}

	// ���������� ���������� X ������ ����� �������
	X = (long) Xc + a * sqrt(1-sqr(Y-Yc)/sqr(b));

	// ������� ������� ������ ������ ������ �� ���� "alfa_radian"
	XX = (long) (X-Xc)*cos(alfa_radian)  - (Y-Yc)*sin(alfa_radian) + Xc;
	YY = (long) (X-Xc)*sin(alfa_radian)  + (Y-Yc)*cos(alfa_radian) + Yc;

	if ((0<=XX) &&  (XX<Xmax) &&  (0<=YY) && (YY<Ymax))
	{
		// ����� � ������������ (X,Y) �������� � ���� �����������

		// ���������� ������� � ������ ���� ���� �������� ���� ����� �����.
		poz = sdw_obl_dan + ((unsigned long)Xmax*3+kol_dobaw)*((unsigned long)YY)+((unsigned long)XX)*3;

		// �������� � ����� ���� ����� �����
		buf[poz]   = cs;
		buf[poz+1] = cz;
		buf[poz+2] = ck;
	}

}


// ����� �� ������� � ��������� ���� ��������� ����������
return 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////// 		������� ��������� ������ ���������� ����� ��� �����		/////////////

//
//
//	������� ��������� :
//				
//		buf 	- ��������� �� ������� ������ � ������� ��������� �����������		
//		X1	- ���������� x ����� � 1
//		Y1	- ���������� y ����� � 1
//		X2	- ���������� x ����� � 2
//		Y2	- ���������� y ����� � 2
//		X3	- ���������� x ����� � 3
//		Y3	- ���������� y ����� � 3
//		cs	- ���� ������ ����� ������������
//		cz	- ���� ������ ������� ������������	
//		ck	- ���� ������ ������� ������������
//
//
//	������������ �������� :		
//
//		1 - ������� �������� ����������, 0 - ������� ���������� ����������
//


int duga( unsigned char * buf, long X1, long Y1, long X2, long Y2, long X3, long Y3, unsigned char cs, unsigned char cz, unsigned char ck )
{

double * matr_X;		// ��������� �� ������� ������������� ������� �������� ���������
double * stolb_Y;		// ��������� �� ������� ��������� ������ ������� �������� ���������
double * xx;		// ��������� �� ������� � ������� ������������ ������� ������� �������� ���������
double opr;		// ������������ ������� ������������� ������� �������� ���������
double a, b, c;		// ������������ ������������� ��������
long X,Y;			// ���������� ����� ������������� �� ����
int nom_oborot;		// ����� ������� ����� ��������� ����
int code_ret;		// ��� ������������ ��� ���������� �������
long Xpred, Ypred;		//  X � Y �� ���������� ������� �����
int priz;			// ������� ����� ��������� �����


// �������� ������� ������ ��� �������� ������� 3 � 3 ������������� ������� �������� ���������
matr_X = (double *) malloc(3*3*sizeof(double)); 

if (matr_X == NULL)
{
	// ������ ��� ��������� ������� ������ ��� �������� ������� 3 � 3 
	// ����� �� ������� � ��������� ���� ���������� ����������
	return 0;
}

// ���������� ������� 3 � 3 ������������� ������� �������� ���������
*(matr_X + 0*3 + 0) = (double) X1*X1;	*(matr_X + 0*3 + 1) = (double) X1;	*(matr_X + 0*3 + 2) = 1.0;
*(matr_X + 1*3 + 0) = (double) X2*X2;	*(matr_X + 1*3 + 1) = (double) X2;	*(matr_X + 1*3 + 2) = 1.0;
*(matr_X + 2*3 + 0) = (double) X3*X3;	*(matr_X + 2*3 + 1) = (double) X3;	*(matr_X + 2*3 + 2) = 1.0;


// �������� ������� ������ ��� �������� ������� ��������� ������ ������� �������� ���������
stolb_Y = (double *) malloc(3*sizeof(double));

if (stolb_Y == NULL)
{
	// ������ ������������ ������ ��� �������� ������� 1 � 3

	// ���������� ����� ���������� ����� ������.
	free(matr_X);

	// ����� �� ������� � ��������� ���� ���������� ����������
	return 0;
}


// ���������� ������� ��������� ������ ������� �������� ���������
*(stolb_Y + 0) = (double) Y1;
*(stolb_Y + 1) = (double) Y2;
*(stolb_Y + 2) = (double) Y3;


// ������� ������� �������� ��������� ������� ������ � ��������� ������������� ������������� ��������
opr=gaus( matr_X, stolb_Y, &xx, 3 );

if (opr!=0.0)
{
	// ������������ �� ����� 0. ������� ������� �������� ��������� �������.

	// ������� ��������� ������������ ��������.
	a = xx[0];
	b = xx[1];
	c = xx[2];

	// ���������� ������� ������ �������� ������� ������� ������� �������� ��������� ���������� �������������� ������������� ��������
	free(xx);

	// ������ ��������� �������� ���������� X � Y
	Xpred = 0;
	Ypred = 0;

	// ������� � ����� ���� ����� ���� � �� ���������

	for (X=X1,nom_oborot=1; X<=X3; X++,nom_oborot++)
	{
		// ���������� ���������� Y ��������� ����� ������
		Y = (long) (a * ((double)X) * ((double)X) + (b * (double)X) + c);

		if (nom_oborot > 1)
		{ 	
			priz = line( buf,   Xpred,Ypred,   X,Y,  cs, cz, ck );
			if (priz !=1) break;
		}
		
		// ��������� ������� �������� ��������� X � Y
		Xpred = X;
		Ypred = Y;
	}

	if (priz)
	{	
		// ���������� ��� �������� ����������
		code_ret = 1;
	}
	else
	{
		// ���������� ��� ���������� ����������.
		code_ret = 0;
	}
	
}
else
{
	// ������������ ����� 0. ������� ������� �������� ��������� �� �������.

	// ���������� ��� ���������� ����������
	code_ret = 0;
}




// ���������� ������� ������ ���������� ��� �������� ������� 3 � 3 ������������� ������� �������� ���������
free(matr_X);

// ���������� ������� ������ ���������� ��� �������� ������� ��������� ������ ������� �������� ���������
free(stolb_Y);




// ����� �� ������� � ��������� ���� ����������
return code_ret;


}

///////////////////////////////////////////////////////////////////////////////////
///////////////////			����� ������� �������			///////////////////////

/*

int main()
{

unsigned long Xmax;	// ������ ����������� � �������� �� �����������
unsigned long Ymax;	// ������ ����������� � �������� �� ���������

unsigned char cs;	// ���� ���� ����� ������������
unsigned char cz;	// ���� ���� ������� ������������
unsigned char ck;	// ���� ���� ������� ������������

int priz;		// ������� �������� ����������
unsigned char * buf;	// ��������� �� �����



// ������ ����������� � �������� �� �����������
Xmax= 106;

// ������ ����������� � �������� �� ���������
Ymax= 100;



// ���� ���� ����� ������������
cs = 255;

// ���� ���� ������� ������������
cz = 255;

// ���� ���� ������� ������������
ck = 255;



// ������������ ������� "create_bmp()"  -  ������� �������� BMP - �����
priz = create_bmp( Xmax, Ymax, cs, cz, ck, &buf );

// ������ ������������ ��������
printf("\n priz =  %d   ",priz );


// ���������� ����� .
priz = point( buf, 30, 1, 0, 0, 0 );

// ������ ������������ ��������
printf("\n priz =  %d   ",priz );


// ���������� �����
priz = line( buf, 50, 50, 50, 10,    0,   0,   0 );
priz = line( buf, 50, 50, 60, 20,   10,  10,  10 );
priz = line( buf, 50, 50, 70, 30,   20,  20,  20 );
priz = line( buf, 50, 50, 80, 40,   30,  30,  30 );
priz = line( buf, 50, 50, 90, 50,   40,  40,  40 );

priz = line( buf, 50, 50, 80, 60,   60,  60,  60 );
priz = line( buf, 50, 50, 70, 70,   70,  70,  70 );
priz = line( buf, 50, 50, 60, 80,   80,  80,  80 );
priz = line( buf, 50, 50, 50, 90,   90,  90,  90 );

priz = line( buf, 50, 50, 40, 80,  100, 100, 100 );
priz = line( buf, 50, 50, 30, 70,  110, 110, 110 );
priz = line( buf, 50, 50, 20, 60,  120, 120, 120 );
priz = line( buf, 50, 50, 10, 50,  130, 130, 130 );

priz = line( buf, 50, 50, 20, 40,  140, 140, 140 );
priz = line( buf, 50, 50, 30, 30,  150, 150, 150 );
priz = line( buf, 50, 50, 40, 20,  160, 160, 160 );
priz = line( buf, 50, 50, 50, 10,  170, 170, 170 );
priz = line( buf, -50, 40, 150, 40,  0, 0, 0 );


priz = krug( buf, 50, 50, 10,   0,  0,  0 );
priz = krug( buf, 50, 50, 20,  10, 10, 10 );
priz = krug( buf, 50, 50, 30,  20, 20, 20 );
priz = krug( buf, 50, 50, 40,  30, 30, 30 );
priz = krug( buf, 50, 50, 50,  40, 40, 40 );
priz = krug( buf, 50, 50, 60,  50, 50, 50 );
priz = krug( buf, 50, 50, 70,  60, 60, 60 );
priz = krug( buf, 110, 100, 40, 0, 0, 0 );

priz = krug( buf, 50, 100,  20, 0, 0, 0 );
priz = krug( buf, 50, 100,  30, 0, 0, 0 );
priz = krug( buf, 50, 100,  40, 0, 0, 0 );
priz = krug( buf, 50, 100,  50, 0, 0, 0 );
priz = krug( buf, 50, 100,  60, 0, 0, 0 );
priz = krug( buf, 50, -20, 80, 0, 0, 0 );
priz = krug( buf, 50, 100,  80, 0, 0, 0 );
priz = krug( buf, 50, 100,  90, 0, 0, 0 );
priz = krug( buf, 50, 100, 100, 0, 0, 0 );
priz = krug( buf, 50, 100, 110, 0, 0, 0 );
priz = krug( buf, 50, 100, 120, 0, 0, 0 );

priz = ellips( buf, 50,50,  40,20,   0, 0,0,0 );
priz = ellips( buf, 50,50,  20,40,  20, 0,0,0 );

priz = ellips( buf, 50,50,  40,20, 235,  0,0,0 );
priz = ellips( buf, 50,50,  20,40,  20, 0,0,0 );
priz = ellips( buf, 50,50,  20,40,  30, 0,0,0 );
priz = ellips( buf, 50,50,  20,40,  40, 0,0,0 );


priz = duga( buf,  0,10,  5,60,  7,94,  0,0,0 );
priz = duga( buf,  5,12.5,  10,40,  20,170,  0,0,0 );
priz = duga( buf,  0,10,  50,60,  100,5,  0,0,0 );
priz = duga( buf,  0,10,  50,60,  100,5,  0,0,0 );

priz = point( buf,   0, 10, 0, 255, 0 );
priz = point( buf,  50, 60, 0, 255, 0 );
priz = point( buf, 100,  5, 0, 255, 0 );

priz =  duga( buf,   0,  20,  50,50,  1,100,  0,0,0 );

priz = point( buf,   0,  20,  0, 255, 0 );
priz = point( buf,  50,  50,  0, 255, 0 );
priz = point( buf,   1, 100,  0, 255, 0 );



// ������������ ������� "save_bmp()" - ������� ���������� BMP - �����
priz = save_bmp("ris2.bmp", buf );

// ������ ������������ ��������
printf("\n priz =  %d   ",priz );


priz = open_bmp( "ris2.bmp", &buf);

// ������ ������������ ��������
printf("\n priz =  %d   ",priz );


return 0;

}

*/

