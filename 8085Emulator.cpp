#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<sstream>

using namespace std;

string mne[30]="";
string instr[65537]="00";
string A="00",B="00",C="00",D="00",E="00",H="00",L="00",M="0000",W="00",Z="00";
string SP="0050",PC="0050",F[8]="0";
int ic=0,ias=50;

string tA="00",tB="00",tC="00",tD="00",tE="00",tH="00",tL="00",tM="0000";
string tSP="0000",tPC="0000",tF[8]="00";
int tias=50;

ifstream fin;

void executer(string);
void mneumonics()
{
   	mne[0]="SET";
	mne[1]="MOV";
	mne[2]="MVI";
	mne[3]="LXI";
	mne[4]="LDA";
	mne[5]="STA";
	mne[6]="LHLD";
	mne[7]="SHLD";
	mne[8]="LDAX";
	mne[9]="STAX";
	mne[10]="XCHG";
	mne[11]="ADD";
	mne[12]="ADI";
	mne[13]="SUB";
	mne[14]="SUI";
	mne[15]="INR";
	mne[16]="DCR";
	mne[17]="INX";
	mne[18]="DCX";
	mne[19]="DAD";
	mne[20]="CMA";
	mne[21]="CMP";
	mne[22]="JMP";
	mne[23]="JC";
	mne[24]="JNC";
	mne[25]="JZ";
	mne[26]="JNZ";
	mne[27]="HLT";
}

void reset()
{
    int i;

    A="00";
    B="00";
    C="00";
    D="00";
    E="00";
    H="00";
    L="00";
    M="0000";
    W="00";
    Z="00";

    for(i=0;i<8;i++)
    {
        F[i]="0";
    }
}

void display()
{
    cout<<"General Purpose Registers:-"<<endl;
    cout<<"A="<<A<<endl;
    cout<<"B="<<B<<endl;
    cout<<"C="<<C<<endl;
    cout<<"D="<<D<<endl;
    cout<<"E="<<E<<endl;
    cout<<"H="<<H<<endl;
    cout<<"L="<<L<<endl;
    cout<<"M="<<M<<endl<<endl;

    cout<<"Special Purpose Registers:-"<<endl;
    cout<<"SP="<<SP<<endl;
    cout<<"PC="<<PC<<endl<<endl;
    cout<<"Flags:-"<<endl;
    cout<<"Sign Flag="<<F[0]<<endl;
    cout<<"Zero Flag="<<F[1]<<endl;
    cout<<"Auxillary Carry Flag="<<F[3]<<endl;
    cout<<"Parity Flag="<<F[5]<<endl;
    cout<<"Carry Flag="<<F[7]<<endl<<endl;
}

void copy_data()
{
    int i;

    tA=A;
    tB=B;
    tC=C;
    tD=D;
    tE=E;
    tH=H;
    tL=L;
    tM=M;

    tSP=SP;
    tPC=PC;

    for(i=0;i<8;i++)
    {
        tF[i]=F[i];
    }

    tias=ias;
}

void revert_back()
{
    int i;

    A=tA;
    B=tB;
    C=tC;
    D=tD;
    E=tE;
    H=tH;
    L=tL;
    M=tM;

    SP=tSP;
    PC=tPC;

    for(i=0;i<8;i++)
    {
        F[i]=tF[i];
    }

    ias=tias;
}

string value_adjuster(string str,int n)
{
    string tstr;
    int l,i,j;

    l=str.length();

    tstr="";
    if(n>l)
    {
        for(i=0;i<(n-l);i++)
        {
            tstr+="0";
        }
        tstr+=str;
    }
    else if(n<l)
    {
        j=l-1;
        for(i=n-1;i>=0;i--)
        {
            tstr=str[j]+tstr;
            j--;
        }
    }
    else
    {
        tstr=str;
    }

    return tstr;
}

string to_case(string str,int mode)
{
    int l,i;

    if(mode==0)
    {
        l=str.length();

        for(i=0;i<l;i++)
        {
            if(str[i]>='A' && str[i]<='Z')
            {
                str[i]+=32;
            }
        }
    }
    if(mode==1)
    {
        l=str.length();

        for(i=0;i<l;i++)
        {
            if(str[i]>='a' && str[i]<='z')
            {
                str[i]-=32;
            }
        }
    }
    return str;
}

string bin_converter(string str)
{
    string res;
    int l,i;

	l=str.length();

	res="";
	for(i=0;i<l;i++)
    {
        switch(str[i])
        {
            case '0':
                    res+="0000";
                    continue;
            case '1':
                    res+="0001";
                    continue;
            case '2':
                    res+="0010";
                    continue;
            case '3':
                    res+="0011";
                    continue;
            case '4':
                    res+="0100";
                    continue;
            case '5':
                    res+="0101";
                    continue;
            case '6':
                    res+="0110";
                    continue;
            case '7':
                    res+="0111";
                    continue;
            case '8':
                    res+="1000";
                    continue;
            case '9':
                    res+="1001";
                    continue;
            case 'A':
                    res+="1010";
                    continue;
            case 'B':
                    res+="1011";
                    continue;
            case 'C':
                    res+="1100";
                    continue;
            case 'D':
                    res+="1101";
                    continue;
            case 'E':
                    res+="1110";
                    continue;
            case 'F':
                    res+="1111";
                    continue;
            default:
                    cout<<"Invalid Data Found!";
                    exit(0);
        }
    }
	return res;
}

string bin_reverter(string str)
{
    string tstr,st;
    int l,i;

    l=str.length();

    st="";
    i=0;
    while(i<l)
    {
        tstr=str.substr(i,(i+4));
        i+=4;

        if(tstr=="0000")
        {
            st+="0";
        }
        else if(tstr=="0001")
        {
            st+="1";
        }
        else if(tstr=="0010")
        {
            st+="2";
        }
        else if(tstr=="0011")
        {
            st+="3";
        }
        else if(tstr=="0100")
        {
            st+="4";
        }
        else if(tstr=="0101")
        {
            st+="5";
        }
        else if(tstr=="0110")
        {
            st+="6";
        }
        else if(tstr=="0111")
        {
            st+="7";
        }
        else if(tstr=="1000")
        {
            st+="8";
        }
        else if(tstr=="1001")
        {
            st+="9";
        }
        else if(tstr=="1010")
        {
            st+="A";
        }
        else if(tstr=="1011")
        {
            st+="B";
        }
        else if(tstr=="1100")
        {
            st+="C";
        }
        else if(tstr=="1101")
        {
            st+="D";
        }
        else if(tstr=="1110")
        {
            st+="E";
        }
        else if(tstr=="1111")
        {
            st+="F";
        }
        else
        {
            cout<<"Invalid Data Found!";
            exit(0);
        }
    }

    return st;
}

void bin_adder(char ch1,char ch2,char *carry,char *res)
{
    int n1,n2,cry,sum,l;

    if(ch1=='0' && ch2=='0')
    {
        n1=0;
        n2=0;
    }
    else if(ch1=='0' && ch2=='1')
    {
        n1=0;
        n2=1;
    }
    else if(ch1=='1' && ch2=='0')
    {
        n1=1;
        n2=0;
    }
    else if(ch1=='1' && ch2=='1')
    {
        n1=1;
        n2=1;
    }
    else
    {
        cout<<"Invalid Data Found!";
        exit(0);
    }

    if(*carry=='0')
    {
        cry=0;
    }
    else if(cry=='1')
    {
        cry=1;
    }

    sum=n1+n2+cry;

    if(sum==2)
    {
        sum=11;
    }

    stringstream ss;
    ss<<sum;
    string str=ss.str();

    l=str.length();

    if(l>1)
    {
        *carry='1';
    }
    else
    {
        *carry='0';
    }
    *res=str[l-1];
}

string IIs_compliment(string str)
{
    string tstr;
    char carry,res;
    int l,i;

    tstr=bin_converter(str);

    l=tstr.length();

    for(i=0;i<l;i++)
    {
        if(tstr[i]=='1')
        {
            tstr[i]='0';
        }
        else
        {
            tstr[i]='1';
        }
    }

    carry='0';
    bin_adder(tstr[l-1],'1',&carry,&res);
    str=res;
    for(i=l-2;i>=0;i--)
    {
        bin_adder(tstr[i],'0',&carry,&res);
        str=res+str;
    }

    l=str.length();
    while(l%4!=0)
    {
        l--;
    }

    str=value_adjuster(str,l);

    str=bin_reverter(str);

    str=value_adjuster(str,2);

    return str;
}

string hex_converter(int n)
{
	stringstream ss;
    ss<<hex<<n;
    string res(ss.str());

	return res;
}

int dec_converter(string str)
{
    int res;

    stringstream ss;
    ss<<str;
    ss>>hex>>res;

	return res;
}

void hex_validator(string str,int mode)
{
    int l,i;

    l=str.length();

    if(mode==0)
    {
        if(l==2)
        {
            for(i=0;i<l;i++)
            {
                switch(str[i])
                {
                    case '0':
                            continue;
                    case '1':
                            continue;
                    case '2':
                            continue;
                    case '3':
                            continue;
                    case '4':
                            continue;
                    case '5':
                            continue;
                    case '6':
                            continue;
                    case '7':
                            continue;
                    case '8':
                            continue;
                    case '9':
                            continue;
                    case 'A':
                            continue;
                    case 'B':
                            continue;
                    case 'C':
                            continue;
                    case 'D':
                            continue;
                    case 'E':
                            continue;
                    case 'F':
                            continue;
                    default:
                            cout<<"Invalid data found!";
                            exit(0);
                }
            }
        }
        else
        {
            cout<<"Invalid data found!";
            exit(0);
        }
    }
    else if(mode==1)
    {
        if(l==4)
        {
            for(i=0;i<l;i++)
            {
                switch(str[i])
                {
                    case '0':
                            continue;
                    case '1':
                            continue;
                    case '2':
                            continue;
                    case '3':
                            continue;
                    case '4':
                            continue;
                    case '5':
                            continue;
                    case '6':
                            continue;
                    case '7':
                            continue;
                    case '8':
                            continue;
                    case '9':
                            continue;
                    case 'A':
                            continue;
                    case 'B':
                            continue;
                    case 'C':
                            continue;
                    case 'D':
                            continue;
                    case 'E':
                            continue;
                    case 'F':
                            continue;
                    default:
                            cout<<"Invalid data found!";
                            exit(0);
                }
            }
        }
        else
        {
            cout<<"Invalid address found!";
            exit(0);
        }
    }
}

string hex_adder(string str1,string str2)
{
    string hexsum,thexsum,temp;
    int intsum,n1,n2,l,i,c;

    n1=dec_converter(str1);
    n2=dec_converter(str2);

    intsum=n1+n2;

    hexsum=hex_converter(intsum);
    hexsum=to_case(hexsum,1);

    if(intsum<0)
    {
        F[0]="1";       //Setting Up Sign Flag
    }
    else
    {
        F[0]="0";
    }

    l=hexsum.length();
    if(l>2)
    {
        F[7]="1";       //Setting Carry Flag
    }
    else
    {
        F[7]="0";
    }

    thexsum=hexsum;
    if(l>2)
    {
        c=0;
        for(i=l-1;i>=0;i--)
        {
            c++;
            if(c==2)
            {
                break;
            }
        }
        thexsum=hexsum.substr(i,l);
    }

    if(thexsum=="00")
    {
        F[1]="1";       //Setting Up Zero Flag
    }
    else
    {
        F[1]="0";
    }

    l=str1.length();
    temp=str1[l-1];
    n1=dec_converter(temp);
    l=str1.length();
    temp=str2[l-1];
    n2=dec_converter(temp);

    intsum=n1+n2;

    temp=hex_converter(intsum);
    l=temp.length();

    if(l>1)
    {
        F[3]="1";       //Setting Up Auxullary Carry Flag
    }
    else
    {
        F[3]="0";
    }

    temp=bin_converter(thexsum);

    l=temp.length();
    c=0;
    for(i=0;i<l;i++)
    {
        if(temp[i]=='1')
        {
            c++;
        }
    }
    if(c%2!=0)
    {
        F[5]="1";       //Setting Up Parity Flag
    }
    else
    {
        F[5]="0";
    }

    return hexsum;
}

string hex_subtracter(string str1,string str2)
{
    string hexdiff,thexdiff,temp;
    int intdiff,flag,n1,n2,l,i,c;

    n1=dec_converter(str1);
    n2=dec_converter(str2);

    intdiff=n1-n2;

    flag=0;
    if(intdiff<0)
    {
        flag=1;
        intdiff=intdiff*-1;
    }
    hexdiff=hex_converter(intdiff);
    hexdiff=to_case(hexdiff,1);

    if(flag==1)
    {
        hexdiff=IIs_compliment(hexdiff);
        intdiff=intdiff*-1;
    }


    hexdiff=value_adjuster(hexdiff,2);
    if(intdiff<0)
    {
        F[0]="1";       //Setting Up Sign Flag
        F[7]="1";       //Setting Carry Flag
    }
    else
    {
        F[0]="0";
        F[7]="0";
    }

    thexdiff=hexdiff;

    if(thexdiff=="00")
    {
        F[1]="1";       //Setting Up Zero Flag
    }
    else
    {
        F[1]="0";
    }

    l=str1.length();
    temp=str1[l-1];
    n1=dec_converter(temp);
    l=str1.length();
    temp=str2[l-1];
    n2=dec_converter(temp);

    intdiff=n1-n2;

    if(intdiff<0)
    {
        F[3]="1";       //Setting Up Auxullary Carry Flag
    }
    else
    {
        F[3]="0";
    }

    temp=bin_converter(thexdiff);

    l=temp.length();
    c=0;
    for(i=0;i<l;i++)
    {
        if(temp[i]=='1')
        {
            c++;
        }
    }
    if(c%2!=0)
    {
        F[5]="1";       //Setting Up Parity Flag
    }
    else
    {
        F[5]="0";
    }

    return hexdiff;
}

string* validate_register(char ch)
{
    int tM;

    switch(ch)
    {
        case 'A':
                hex_validator(A,0);
                return (&A);
        case 'B':
                hex_validator(B,0);
                return (&B);
        case 'C':
                hex_validator(C,0);
                return (&C);
        case 'D':
                hex_validator(D,0);
                return (&D);
        case 'E':
                hex_validator(E,0);
                return (&E);
        case 'H':
                hex_validator(H,0);
                return (&H);
        case 'L':
                hex_validator(L,0);
                return (&L);
        case 'M':
                hex_validator(H,0);
                M=H;
                hex_validator(L,0);
                M+=L;

                tM=dec_converter(M);
                return (&(instr[tM]));
        default:
                cout<<"No valid register found!";
                exit(0);
    }
}

string* validate_address(string str)
{
    int temp,l;

    l=str.length();

    if(l==4)
    {
        hex_validator(str,1);

        temp=dec_converter(str);

        if(temp>=0 && temp<=65535)
        {
            hex_validator(instr[temp],0);

            return (&instr[temp]);
        }
    }
}

int mneuonics_validator(string st)
{
    int flag,i;

    flag=0;
    for(i=0;i<28;i++)
    {
        if(mne[i]==st)
        {
            flag=1;
            return i;
        }
    }

    if(flag==0)
    {
        cout<<"Mneumonic not found!";
        exit(0);
    }
}

void SET(string str)
{
    string t1str,t2str,tstr;
    int temp1,l;

    l=str.length();
    if(l==7)
    {
        if(str[4]==',')
        {
            t1str=str.substr(0,4);

            hex_validator(t1str,1);

            temp1=dec_converter(t1str);

            t2str=str.substr(5,6);

            hex_validator(t2str,0);

            instr[temp1]=t2str;
            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
    }
    else
    {
        cout<<"Invalid Instruction found"<<endl<<endl;
        display();
        exit(0);
    }
}

void MOV(string str)
{
    string *rg1,*rg2;
    string tstr;
    int l;

    rg1=NULL;
    rg2=NULL;

    l=str.length();

    if(l==3)
    {
        if(str[1]==',')
        {
            rg1=validate_register(str[0]);
            rg2=validate_register(str[2]);

            *rg1=*rg2;
            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Syntax error found";
            cout<<"Instruction Number:"<<(ic-1)<<endl<<endl;
            display();
            exit(0);
        }
    }
    else if(l==6)
    {
        if(str[1]==',')
        {
            rg1=validate_register(str[0]);
            tstr=str.substr(2,l);

            rg2=validate_address(tstr);

            *rg1=*rg2;
            ias+=3;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else if(str[4]==',')
        {
            tstr=str.substr(0,4);
            rg1=validate_address(tstr);

            rg2=validate_register(str[5]);

            *rg1=*rg2;
            ias+=3;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Invalid operand found!"<<endl<<endl;
            display();
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!"<<endl<<endl;
        display();
        exit(0);
    }
}

void MVI(string str)
{
    string *rg,val,tstr;
    int l;

    l=str.length();

    rg=NULL;
    if(l==4)
    {
        if(str[1]==',')
        {
            rg=validate_register(str[0]);

            val=str.substr(2,l);

            hex_validator(val,0);

            *rg=val;

            ias+=2;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Invalid operand found!"<<endl<<endl;
            display();
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!"<<endl<<endl;
        display();
        exit(0);
    }
}

void LXI(string str)
{
    string *rg,val,*dummy,tstr;
    int l,temp;

    l=str.length();

    rg=NULL;
    if(l==6)
    {
        if(str[1]==',')
        {
            rg=validate_register(str[0]);

            if(str[0]=='B' || str[0]=='D' || str[0]=='H')
            {
                val=str.substr(2,l);

                dummy=NULL;
                dummy=validate_address(val);

                temp=dec_converter(val);
                if(temp>=0 && temp<50)
                {
                    if(str[0]=='B')
                    {
                        B=str.substr(2,2);
                        C=str.substr(4,6);
                    }
                    else if(str[0]=='D')
                    {
                        D=str.substr(2,2);
                        E=str.substr(4,6);
                    }
                    else
                    {
                        H=str.substr(2,2);
                        L=str.substr(4,6);
                    }
                    ias+=2;

                    tstr=hex_converter(ias);
                    PC=value_adjuster(tstr,4);
                }
                else
                {
                    cout<<"Address mentioned is out of assigned range!"<<endl<<endl;
                    display();
                    exit(0);
                }
            }
            else
            {
                cout<<"Valid register for this operation not found!"<<endl<<endl;
                display();
                exit(0);
            }
        }
        else
        {
            cout<<"Invalid operand found!"<<endl<<endl;
            display();
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!"<<endl<<endl;
        display();
        exit(0);
    }
}

void LDA(string str)
{
    string *val,tstr;
    val=NULL;

    val=validate_address(str);

    A=*val;

    ias+=2;

    tstr=hex_converter(ias);
    PC=value_adjuster(tstr,4);
}

void STA(string str)
{
    string *dummy,tstr;
    int pos;

    dummy=NULL;
    dummy=validate_address(str);

    pos=dec_converter(str);

    instr[pos]=A;

    ias+=2;

    tstr=hex_converter(ias);
    PC=value_adjuster(tstr,4);
}

void LHLD(string str)
{
    string *pstr,tstr;
    int temp;

    pstr=NULL;
    pstr=validate_address(str);

    L=*pstr;

    tstr=hex_adder(str,"1");

    tstr=value_adjuster(tstr,4);

    temp=dec_converter(tstr);

    if(temp<50)
    {
        pstr=NULL;
        pstr=validate_address(tstr);

        H=*pstr;
    }
    else
    {
        cout<<"Address mentioned is out of assigned range!"<<endl<<endl;
        display();
        exit(0);
    }

    ias+=3;

    tstr=hex_converter(ias);
    PC=value_adjuster(tstr,4);
}

void SHLD(string str)
{
    string tstr;
    int temp;

    hex_validator(str,1);

    temp=dec_converter(str);

    if(temp>=0 && temp<50)
    {
        instr[temp]=L;
    }
    else
    {
        cout<<"Address mentioned is out of assigned range!"<<endl<<endl;
        display();
        exit(0);
    }

    tstr=hex_adder(str,"1");

    temp=dec_converter(tstr);

    if(temp>=0 && temp<50)
    {
        instr[temp]=H;
    }

    ias+=3;

    tstr=hex_converter(ias);
    PC=value_adjuster(tstr,4);
}

void LDAX(string str)
{
    string tstr;
    int l,temp;

    l=str.length();

    if(l==1)
    {
        validate_register(str[0]);

        if((str[0]=='B') || (str[0]=='D') || (str[0]=='H'))
        {
            str="";

            if(str[0]=='B')
            {
                tstr=B;
                tstr+=C;
            }
            else if(str[0]=='D')
            {
                tstr=D;
                tstr+=E;
            }
            else
            {
                tstr=H;
                tstr+=L;
            }

            temp=dec_converter(tstr);

            A=instr[temp];

            ias+=2;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Valid register not found!"<<endl<<endl;
            display();
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!"<<endl<<endl;
        display();
        exit(0);
    }
}

void STAX(string str)
{
    string tstr;
    int pos;

    hex_validator(str,1);

    pos=dec_converter(str);

    if(pos>=0 && pos<50)
    {
        instr[pos]=A;

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else
    {
        cout<<"Address mentioned is out of assigned range!"<<endl<<endl;
        display();
        exit(0);
    }
}

void XCHG()
{
    string tstr;

    hex_validator(H,0);
    hex_validator(D,0);
    W=H;
    H=D;
    D=W;

    hex_validator(L,0);
    hex_validator(E,0);
    Z=L;
    L=E;
    E=Z;

    ias+=1;

    tstr=hex_converter(ias);
    PC=value_adjuster(tstr,4);
}

void ADD(string str)
{
    string *pstr,tstr;
    int l,temp;

    l=str.length();

    pstr==NULL;
    if(l==1)
    {
        pstr=validate_register(str[0]);

        tstr=hex_adder(A,*pstr);

        tstr=value_adjuster(tstr,2);

        A=to_case(tstr,1);

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else if(l==4)
    {
        temp=dec_converter(str);

        if(temp>=0 && temp<50)
        {
            pstr=validate_address(str);

            temp=dec_converter(*pstr);

            stringstream ss;
            ss<<temp;
            string str=ss.str();

            tstr=hex_adder(A,str);
            tstr=value_adjuster(tstr,2);

            A=to_case(tstr,1);

            ias+=3;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Address out of assigned range found!";
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!";
        exit(0);
    }
}

void ADI(string str)
{
    string tstr;
    int l;

    l=str.length();

    if(l==2)
    {
        hex_validator(str,0);

        tstr=hex_adder(A,str);

        A=value_adjuster(tstr,2);

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void SUB(string str)
{
    string *pstr,tstr,t;
    int l,temp;

    l=str.length();

    pstr==NULL;
    if(l==1)
    {
        pstr=validate_register(str[0]);

        tstr=hex_subtracter(A,*pstr);

        t=value_adjuster(tstr,2);

        A=to_case(t,1);

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else if(l==4)
    {
        temp=dec_converter(str);

        if(temp>=0 && temp<50)
        {
            pstr=validate_address(str);

            temp=dec_converter(*pstr);

            stringstream ss;
            ss<<temp;
            string str=ss.str();

            tstr=hex_subtracter(A,str);

            tstr=value_adjuster(tstr,2);

            A=to_case(tstr,1);

            ias+=3;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            cout<<"Address out of assigned range found!";
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid operand found!";
        exit(0);
    }
}

void SUI(string str)
{
    string tstr;
    int l;

    l=str.length();

    if(l==2)
    {
        hex_validator(str,0);

        tstr=hex_subtracter(A,str);

        A=value_adjuster(tstr,2);

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void INR(string str)
{
    string *val,tstr,add;
    int l,temp;

    l=str.length();

    if(l==1)
    {
        val=validate_register(str[0]);

        if(str[0]!='M')
        {
            tstr=hex_adder(*val,"1");

            tstr=value_adjuster(tstr,2);

            *val=tstr;

            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            add=L;
            add=H+add;

            temp=dec_converter(add);
            tstr=hex_adder(instr[temp],"1");

            instr[temp]=tstr;

            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void DCR(string str)
{
    string *val,tstr,add;
    int l,temp;

    l=str.length();

    if(l==1)
    {
        val=validate_register(str[0]);

        if(str[0]!='M')
        {
            tstr=hex_subtracter(*val,"1");

            tstr=value_adjuster(tstr,2);

            *val=tstr;

            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
        else
        {
            add=L;
            add=H+add;

            temp=dec_converter(add);
            tstr=hex_subtracter(instr[temp],"1");

            instr[temp]=tstr;

            ias+=1;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);
        }
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void INX(string str)
{
    string *dptr,t1str,t2str,tstr;
    int l;

    l=str.length();

    if(l==1)
    {
        dptr=validate_register(str[0]);

        if((str[0]=='B')||(str[0]=='D')||(str[0]=='H'))
        {
            copy_data();
            if(str[0]=='B')
            {
                t1str=C;
                t2str=B;

                t1str=hex_adder(C,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_adder(B,"1");

                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                C=t1str;
                B=t2str;

                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else if(str[0]=='D')
            {
                t1str=E;
                t2str=D;

                t1str=hex_adder(E,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_adder(D,"1");
                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                E=t1str;
                D=t2str;


                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else
            {
                t1str=L;
                t2str=H;

                t1str=hex_adder(L,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_adder(H,"1");
                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                L=t1str;
                H=t2str;

                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
        }
        else
        {
            cout<<"Valid register not found!";
            exit(0);
        }
    }
}

void DCX(string str)
{
    string *dptr,t1str,t2str,tstr;
    int l;

    l=str.length();

    if(l==1)
    {
        dptr=validate_register(str[0]);

        if((str[0]=='B')||(str[0]=='D')||(str[0]=='H'))
        {
            copy_data();
            if(str[0]=='B')
            {
                t1str=C;
                t2str=B;

                t1str=hex_subtracter(C,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_subtracter(B,"1");

                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                C=t1str;
                B=t2str;

                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else if(str[0]=='D')
            {
                t1str=E;
                t2str=D;

                t1str=hex_subtracter(E,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_subtracter(D,"1");
                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                E=t1str;
                D=t2str;

                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else
            {
                t1str=L;
                t2str=H;

                t1str=hex_subtracter(L,"1");
                l=t1str.length();

                if(l>2)
                {
                    t2str=hex_subtracter(H,"1");
                }
                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                revert_back();

                L=t1str;
                H=t2str;

                ias+=1;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
        }
        else
        {
            cout<<"Valid register not found!";
            exit(0);
        }
    }
}

void DAD(string str)
{
    string *dptr,t1str,t2str,tstr,temp;
    int l;

    l=str.length();

    if(l==1)
    {
        dptr=validate_register(str[0]);

        if((str[0]=='B')||(str[0]=='D')||(str[0]=='H'))
        {
            if(str[0]=='B')
            {
                t1str="";
                t2str="";

                t1str=hex_adder(L,C);
                l=t1str.length();

                t2str=hex_adder(H,B);

                if(l>2)
                {
                    temp=t1str[0];
                    t2str=hex_adder(t2str,temp);
                }

                reset();

                l=t2str.length();
                if(l>2)
                {
                    F[7]="1";
                }
                else
                {
                    F[7]="0";
                }

                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                L=t1str;
                H=t2str;

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else if(str[0]=='D')
            {
                t1str="";
                t2str="";

                t1str=hex_adder(L,E);
                l=t1str.length();

                t2str=hex_adder(H,D);

                if(l>2)
                {
                    temp=t1str[0];
                    t2str=hex_adder(t2str,temp);
                }

                reset();

                l=t2str.length();
                if(l>2)
                {
                    F[7]="1";
                }
                else
                {
                    F[7]="0";
                }

                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                L=t1str;
                H=t2str;

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
            else
            {
                t1str="";
                t2str="";

                t1str=hex_adder(L,L);
                l=t1str.length();

                t2str=hex_adder(H,H);

                if(l>2)
                {
                    temp=t1str[0];
                    t2str=hex_adder(t2str,temp);
                }

                reset();

                l=t2str.length();
                if(l>2)
                {
                    F[7]="1";
                }
                else
                {
                    F[7]="0";
                }

                t1str=value_adjuster(t1str,2);
                t2str=value_adjuster(t2str,2);

                L=t1str;
                H=t2str;

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);
            }
        }
        else
        {
            cout<<"Valid register not found!";
            exit(0);
        }

    }
}

void CMA(string str)
{
    string tstr;
    int l,i;

    l=str.length();

    if(l==0)
    {
        tstr=bin_converter(A);

        l=tstr.length();

        for(i=0;i<l;i++)
        {
           if(tstr[i]=='1')
           {
               tstr[i]='0';
           }
           else if(tstr[i]=='0')
           {
               tstr[i]='1';
           }
           else
           {
               cout<<"Error";
               exit(0);
           }
        }

        tstr=bin_reverter(tstr);

        A=tstr;

        tstr=hex_adder(A,"0");

        ias+=1;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else
    {
        cout<<"Invalid Instruction Found!";
        exit(0);
    }
}

void CMP(string str)
{
    string *ptr,tstr;
    int l;

    l=str.length();

    if(l==1)
    {
        ptr=NULL;
        ptr=validate_register(str[0]);

        tstr=hex_subtracter(A,*ptr);

        ias+=2;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else if(l==4)
    {
        ptr=NULL;
        ptr=validate_address(str);

        tstr=hex_subtracter(A,*ptr);

        ias+=3;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void JMP(string str)
{
    string *val,tstr;
    int l,add,temp;

    l=str.length();

    if(l==4)
    {
        hex_validator(str,1);

        add=dec_converter(str);

        if(add<=ias)
        {
            temp=ias;

            ias=add;
            while(ias<temp)
            {
                executer(instr[ias]);
            }

            executer(instr[ias]);
        }
        else
        {
            hex_validator(str,1);

            add=dec_converter(str);

            ias+=3;

            tstr=hex_converter(ias);
            PC=value_adjuster(tstr,4);


            copy_data();

            temp=ias;
            while(ias<add)
            {
                getline(fin,tstr);

                instr[ias]=tstr;

                executer(instr[ias]);

                ic++;
            }
            if(ias>add)
            {
                cout<<"Address mentioned is not proper";
                exit(0);
            }
            revert_back();
        }
    }
    else
    {
        cout<<"Invalid Operand Found!";
        exit(0);
    }
}

void JC(string str)
{
    string *val,tstr;
    int l,add,temp;

    if(F[7]=="1")
    {
        l=str.length();

        if(l==4)
        {
            hex_validator(str,1);

            add=dec_converter(str);

            if(add<=ias)
            {
                temp=ias;

                ias=add;
                while(ias<temp)
                {
                    executer(instr[ias]);
                }

                executer(instr[ias]);
            }
            else
            {
                hex_validator(str,1);

                add=dec_converter(str);

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);


                copy_data();

                temp=ias;
                while(ias<add)
                {
                    getline(fin,tstr);

                    instr[ias]=tstr;

                    executer(instr[ias]);

                    ic++;
                }
                if(ias>add)
                {
                    cout<<"Address mentioned is not proper";
                    exit(0);
                }
                revert_back();
            }
        }
        else
        {
            cout<<"Invalid Operand Found!";
            exit(0);
        }
    }
    else
    {
        ias+=3;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);

    }
}

void JNC(string str)
{
    string *val,tstr;
    int l,add,temp;

    if(F[7]!="1")
    {
        l=str.length();

        if(l==4)
        {
            hex_validator(str,1);

            add=dec_converter(str);

            if(add<=ias)
            {
                temp=ias;

                ias=add;
                while(ias<temp)
                {
                    executer(instr[ias]);
                }

                executer(instr[ias]);
            }
            else
            {
                hex_validator(str,1);

                add=dec_converter(str);

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);


                copy_data();

                temp=ias;
                while(ias<add)
                {
                    getline(fin,tstr);

                    instr[ias]=tstr;

                    executer(instr[ias]);

                    ic++;
                }
                if(ias>add)
                {
                    cout<<"Address mentioned is not proper";
                    exit(0);
                }
                revert_back();
            }
        }
        else
        {
            cout<<"Invalid Operand Found!";
            exit(0);
        }
    }
    else
    {
        ias+=3;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);

    }
}

void JZ(string str)
{
    string *val,tstr;
    int l,add,temp;

    if(F[1]=="1")
    {
        l=str.length();

        if(l==4)
        {
            hex_validator(str,1);

            add=dec_converter(str);

            if(add<=ias)
            {
                temp=ias;

                ias=add;
                while(ias<temp)
                {
                    executer(instr[ias]);
                }

                executer(instr[ias]);
            }
            else
            {
                hex_validator(str,1);

                add=dec_converter(str);

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);


                copy_data();

                temp=ias;
                while(ias<add)
                {
                    getline(fin,tstr);

                    instr[ias]=tstr;

                    executer(instr[ias]);

                    ic++;
                }
                if(ias>add)
                {
                    cout<<"Address mentioned is not proper";
                    exit(0);
                }
                revert_back();
            }
        }
        else
        {
            cout<<"Invalid Operand Found!";
            exit(0);
        }
    }
    else
    {
        ias+=3;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);

    }
}

void JNZ(string str)
{
    string *val,tstr;
    int l,add,temp;

    if(F[1]!="1")
    {
        l=str.length();

        if(l==4)
        {
            hex_validator(str,1);

            add=dec_converter(str);

            if(add<=ias)
            {
                temp=ias;

                ias=add;
                while(ias<temp)
                {
                    executer(instr[ias]);
                }

                executer(instr[ias]);
            }
            else
            {
                hex_validator(str,1);

                add=dec_converter(str);

                ias+=3;

                tstr=hex_converter(ias);
                PC=value_adjuster(tstr,4);


                copy_data();

                temp=ias;
                while(ias<add)
                {
                    getline(fin,tstr);

                    instr[ias]=tstr;

                    executer(instr[ias]);

                    ic++;
                }
                if(ias>add)
                {
                    cout<<"Address mentioned is not proper";
                    exit(0);
                }
                revert_back();
            }
        }
        else
        {
            cout<<"Invalid Operand Found!";
            exit(0);
        }
    }
    else
    {
        ias+=3;

        tstr=hex_converter(ias);
        PC=value_adjuster(tstr,4);

    }
}

void HLT(string str)
{
    int l,i;

    l=str.length();

    if(l==0)
    {
        display();

        for(i=0;i<100;i++)
        {
            cout<<instr[i]<<endl;
            if(instr[i]=="HLT")
            {
                break;
            }
        }
        exit(0);
    }
    else
    {
        cout<<"Invalid Instruction Found!";
        exit(0);
    }
}

void executer(string str)
{
    string tstr,ttstr;
    int opcode,isize,l,i;

    l=str.length();

    i=0;
    while(str[i]!=' ')
    {
        if(i==l)
        {
            break;
        }
        i++;
    }

    tstr=str.substr(0,i);

    ttstr=to_case(tstr,1);

    opcode=mneuonics_validator(ttstr);

    tstr="";
    l=str.length();
    if(i!=l)
    {
        tstr=str.substr((i+1),l);
    }

    if(opcode==0)
    {
       SET(tstr);
    }
    else if(opcode==1)
    {
        MOV(tstr);
    }
    else if(opcode==2)
    {
        MVI(tstr);
    }
    else if(opcode==3)
    {
        LXI(tstr);
    }
    else if(opcode==4)
    {
        LDA(tstr);
    }
    else if(opcode==5)
    {
        STA(tstr);
    }
    else if(opcode==6)
    {
        LHLD(tstr);
    }
    else if(opcode==7)
    {
        SHLD(tstr);
    }
    else if(opcode==8)
    {
        LDAX(tstr);
    }
    else if(opcode==9)
    {
        STAX(tstr);
    }
    else if(opcode==10)
    {
        XCHG();
    }
    else if(opcode==11)
    {
        ADD(tstr);
    }
    else if(opcode==12)
    {
        ADI(tstr);
    }
    else if(opcode==13)
    {
        SUB(tstr);
    }
    else if(opcode==14)
    {
        SUI(tstr);
    }
    else if(opcode==15)
    {
        INR(tstr);
    }
    else if(opcode==16)
    {
        DCR(tstr);
    }
    else if(opcode==17)
    {
        INX(tstr);
    }
    else if(opcode==18)
    {
        DCX(tstr);
    }
    else if(opcode==19)
    {
        DAD(tstr);
    }
    else if(opcode==20)
    {
        CMA(tstr);
    }
    else if(opcode==21)
    {
        CMP(tstr);
    }
    else if(opcode==22)
    {
        JMP(tstr);
    }
    else if(opcode==23)
    {
        JC(tstr);
    }
    else if(opcode==24)
    {
        JNC(tstr);
    }
    else if(opcode==25)
    {
        JZ(tstr);
    }
    else if(opcode==26)
    {
        JNZ(tstr);
    }
    else if(opcode==27)
    {
        HLT(tstr);
    }
    else
    {
        cout<<"Invalid Opcode Found!";
        exit(0);
    }
}

int debug(char **argv1)
{

    string str,tstr;
    int l,tc;

    fin.open("help.txt");
    while(getline(fin,str) )
    {
        cout<<str<<endl;
    }
    fin.close();
    cout<<endl;

    while(1)
    {
        cout<<"-->";
        getline(cin,str);

        tstr=to_case(str,0);
        str=tstr;
        l=str.length();
        if(l==1)
        {
            if(str[0]=='r')
            {
                fin.open("sample.txt");//fin.open(*argv1);

                if(ias<=65534)
                {
                    tc=0;
                    while(tc<ic)
                    {
                        getline(fin,tstr);
                        tc++;
                    }

                    while(1)
                    {
                        getline(fin,tstr);
                        instr[ias]=to_case(tstr,1);

                        tstr=hex_converter(ias);
                        SP=value_adjuster(tstr,4);

                        if((ias==655532) || (ias==655533) || (ias==655534))
                        {
                            copy_data();
                        }

                        executer(instr[ias]);

                        if(ias>65534)
                        {
                            revert_back();
                            cout<<"Memory Limit reached!"<<endl;
                            cout<<"Program ran till instruction number:-"<<ic<<endl;
                            exit(0);
                        }
                        ic++;
                    }
                }
                else
                {
                    cout<<"Memory Limit reached!";
                    exit(0);
                }
                display();

                fin.close();
            }
            else if(str[0]=='s')
            {
                fin.open("sample.txt");//fin.open(*argv1);

                if(ias<=65534)
                {
                    tc=0;
                    while(tc<ic)
                    {
                        getline(fin,tstr);
                        tc++;
                    }

                    getline(fin,tstr);
                    instr[ias]=to_case(tstr,1);

                    tstr=hex_converter(ias);
                    SP=value_adjuster(tstr,4);


                    if((ias==655532) || (ias==655533) || (ias==655534))
                    {
                        copy_data();
                    }

                    executer(instr[ias]);

                    if(ias>65534)
                    {
                        revert_back();
                        cout<<"Memory Limit reached!"<<endl;
                        cout<<"Program ran till instruction number:-"<<ic<<endl;
                        exit(0);
                    }

                    ic++;
                }
                else
                {
                    cout<<"Memory Limit Reached!";
                    exit(0);
                }
                display();

                fin.close();
            }
            else if(str[0]=='q')
            {
                exit(0);
            }
            else if(str[0]=='h')
            {
                fin.open("help.txt");
                while( getline(fin,str) )
                {
                    cout<<str<<endl;
                }
                 fin.close();
                cout<<endl;
            }
            else
            {
                cout<<"Invalid Choice entered!"<<endl<<endl;
            }
        }
        else if(l==3)
        {
            if(str[0]=='p')
            {
                string *rgvalue;

                rgvalue=NULL;
                rgvalue=validate_register(str[2]);

                if((rgvalue)!=NULL)
                {
                    cout<<str[2]<<" = "<<(*rgvalue)<<endl;
                }
            }
            else
            {
                cout<<"Invalid Choice entered!"<<endl<<endl;
            }
        }
        else if(l==6)
        {
            if(str[0]=='p')
            {
                string *addvalue=NULL;
                string tstr=str.substr(2,l);

                addvalue=validate_address(tstr);

                if((*addvalue)!="NULL")
                {
                    cout<<tstr<<" = "<<*addvalue<<endl;
                }
            }
            else if(str[0]=='b')
            {
                string tstr;
                int ttc;

                tstr=str.substr(2,l);
                hex_validator(tstr,1);

                tc=dec_converter(tstr);
                tc+=ic;

                fin.open("sample.txt");//fin.open(*argv1);
                if(ias<=65534)
                {
                    ttc=0;
                    while(ttc<ic)
                    {
                        getline(fin,tstr);
                        tc++;
                    }
                }

                while(ttc<=tc)
                {
                    getline(fin,tstr);
                    instr[ias]=to_case(tstr,1);

                    tstr=hex_converter(ias);
                    SP=value_adjuster(tstr,4);


                    if((ias==655532) || (ias==655533) || (ias==655534))
                    {
                        copy_data();
                    }

                    executer(instr[ias]);

                    if(ias>65534)
                    {
                        revert_back();
                        display();
                        cout<<"Memory Limit reached!"<<endl;
                        cout<<"Program ran till instruction number:-"<<ttc<<endl;
                        exit(0);
                    }
                    ic++;
                }
                fin.close();
            }
            else
            {
                cout<<"Invalid Choice entered!"<<endl<<endl;
            }
        }
        else
        {
            cout<<"Wrong choice entered"<<endl;
            cout<<"To run Debugger according to your choice, Please only enter the initials"<<endl;
            cout<<"For more information--Press h"<<endl<<endl;
        }
    }

    return 0;
}

void getdata()
{
    string ind,tind,str;

    while(1)
    {
        tind=hex_converter(ias);
        ind=to_case(tind,1);
        if(ias<=65534)
        {
            ind=value_adjuster(ind,4);

            cout<<ind<<"  ";

            getline(cin,str);
            instr[ias]=to_case(str,1);

            if(instr[ias][0]=='\0')
            {
                display();
                exit(0);
            }

            executer(instr[ias]);
        }
        else
        {
            cout<<"Memory limit reached!"<<endl<<endl;
            display();
            exit(0);
        }
    }
    display();
}

int main(int argc,char *argv[])
{
    mneumonics();

    if(argc==2)
    {
        debug(&argv[1]);
    }
    else
    {
         getdata();
    }

    return 0;
}
