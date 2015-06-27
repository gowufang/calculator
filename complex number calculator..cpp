#include<iostream> 
#include<cmath> 
#include<cstdlib> 
#include<cstring> 
#include<fstream>  
#include<ctime> 

#define EPS 1e-5                //���徫�ȳ���

using namespace std;            //ʹ�ñ�׼�ռ�����std
namespace NameCCom          //���������ռ�NameCCom
{ 
  class CCom               //����һ��CCom��
  {  
    public: 
      double Real,Image;
    CCom(double real=0,double image=0)         //���캯��
    { 
      Real=real; 
      Image=image; 
    } 
     friend istream & operator>>(istream &is,CCom &com);        //��������
     friend ostream & operator<<(ostream &os,CCom &com);        //�������
     CCom operator+(CCom &com);                             //�ӷ�����
     CCom operator-(CCom &com);                              //��������
     CCom operator*(CCom &com);                             //�˷�����
     CCom operator/(CCom &com);                               //��������
     CCom operator+=(CCom &com);                             //�ӷ���ֵ����
     CCom operator-=(CCom &com);                             //������ֵ����
     CCom operator*=(CCom &com);                            //�˷���ֵ����
     CCom operator/=(CCom &com);                            //������ֵ����
     double mod(void);                                        //������ģ
     int operator>(CCom &com); 
     int operator<(CCom &com); 
     int operator!=(CCom &com); 
     int operator==(CCom &com); 
  };   
                  
  struct User          //�����û��ṹ������          
  { 
    char szName[20];     //�û���
    int nTime;           //ʹ�ô���
    int nTest;           //���Դ���
    double alAve;        //ƽ���ɼ�  
    int nAdd;            //�ӷ�����
    int nSub;            //�������� 
    int nMul;            //�˷�����
    int nDiv;            //��������
    double dlScore[3];   //3�β��Ե÷�
  }user;             //����ȫ�ֱ���

  double CCom::mod()            //������ģ������ʵ��ƽ�����鲿ƽ���͵Ŀ���
  { 
    return sqrt(Real*Real+Image*Image); 
  } 
  int CCom::operator>(CCom &com)    //���������">"���Ƚ�ģ�Ĵ�С
  { 
    if(mod()>com.mod()) 
      return 1;    //�����򷵻�1
    else 
      return 0;    //�����򷵻�0
  } 
  int CCom::operator<(CCom &com)    //���������"<"���Ƚ�ģ�Ĵ�С
  { 
    if(mod()<com.mod())     
      return 1;           //��С���򷵻�1
    else                                                             
      return 0;           //�����򷵻�0
  } 
  int CCom::operator!=(CCom &com)   //���������"!="���ֱ��жϸ�����ʵ�����鲿 
  { 
    if(*this==com) 
      return 0;           //����ȣ��򷵻�0
    else  
      return 1;           //�����򷵻�1
  } 

  istream & operator>>(istream &is,CCom &com) //�������룬��������a+bi����ʽ
  { 
    cout<<"�����븴��:"; 
    char s[80]; 
    is>>s;                   //���ַ�������ʽ���ܸ���
    int len=strlen(s);       //����ַ����ĳ���
    int n=0,sign=1; //nΪ��ǰ���ַ�������ȡ���������֣���ʼ��Ϊ0��sign�Ǳ�Ƿ��ţ���ʼ��Ϊ��
    com.Image=com.Real=0; 
    for(int k=0;k<len;k++)   //�жϽ��ܵ��ַ����Ƿ�Ϸ�
    { 
      if((s[k]<'0' || s[k]> '9') && (s[k]!='+' && s[k]!='-' && s[k]!='i')) 
      { 
        cout<<"error"<<endl;     
        return is;          //�������������Ϣ������
      } 
    } 
    for(k=0;k<len;)     //˳��ʶ���ַ����и��ַ�
    { 
      if(n!=0 &&(s[k]=='-'||s[k]=='+'))    //��ǰ�ַ��Ƿ��Ƿ���λ
      { 
        com.Real=sign*n;  //sign�Ƿ���λ����n!=0����n�ѱ���ֵ��������ǰ��ȡ�����鲿�ķ���
        n=0;             //��ԭn*signֵ����ʵ������n���㣬׼�������鲿��ֵ
      } 
      if(s[k]=='-')    //��ǰ�ַ�Ϊ����
      { 
        sign=-1;k++;      //�����ű�־��ֵ
      } 
      if(s[k]=='+')    //��ǰ�ַ�Ϊ����
      { 
        sign=1;k++;      //�����ű�־��ֵ
      } 
      if(s[k]=='i')    //��ǰ�ַ�Ϊ'i'
      { 
        if(k!=len-1)       //�ж��ַ�'i'�Ƿ�Ϊ�ַ���������һ���ַ�
          cout<<"error\n";    //������ǣ�˵���������ݸ�ʽ����
        else  
          com.Image=sign*n;   //��������һ���ַ������������ѽ����꣬��sign*nΪ�鲿��ֵ 
        break; 
      } 
      while(s[k]>='0' && s[k]<='9')   //�����ǰ�ַ���0��9֮�䣬�������ַ�ת����������ֵ
      { 
        n=n*10+s[k]-'0'; 
        k++; 
      } 
    } 
    if(s[len-1]!='i' && n!=0)        //������һ���ַ�����'i'����ʾ����������ֻ��ʵ����û���鲿 
    { 
      com.Real=n*sign; 
    } 
    return is; 
  } 

  ostream & operator<<(ostream &os,CCom &com)  //�������� 
  { 
    if(fabs(com.Image)<EPS)       // ����鲿Ϊ0
      os<<com.Real;          //ֻ���ʵ��
    else if((fabs(com.Real)<EPS))   //���ʵ��Ϊ0
           os<<com.Image<<"i";    //ֻ����鲿
         else if(com.Image>0) 
                os<<com.Real<<"+"<<com.Image<<"i"; 
              else 
                os<<com.Real<<com.Image<<"i";    //�鲿Ϊ��
    return os; 
  } 

  CCom CCom::operator+(CCom &com)   //�ӷ�����
  { 
    CCom sum; 
    sum.Real=Real+com.Real;     //ʵ�����
    sum.Image=Image+com.Image;  //�鲿���
    return sum; 
  }
  CCom CCom::operator-(CCom &com)  //�������� 
  { 
    CCom sub; 
    sub.Real=Real-com.Real;        //ʵ�����
    sub.Image=Image-com.Image;      //�鲿���
    return sub; 
  } 
  CCom CCom::operator*(CCom &com)   //�˷�����
  { 
    CCom multi; 
    multi.Real=Real*com.Real-Image*com.Image;  //ʵ���˻�
    multi.Image=Real*com.Image+Image*com.Real; //�鲿�˻�
    return multi; 
  } 
  CCom CCom::operator/(CCom &com)   //��������
  { 
    CCom div; 
    div.Real=(Real*com.Real+Image*com.Image)/(com.Real*com.Real+com.Image*com.Image); //ʵ������
    div.Image=(Image*com.Real-Real*com.Image)/(com.Real*com.Real+com.Image*com.Image); //�鲿����
    return div; 
  } 
  CCom CCom::operator+=(CCom &com) //���ؼӷ���ֵ
  { 
    Real=Real+com.Real;             //ʵ�����
    Image=Image+com.Image;          //�鲿���
    return *this; 
  } 
  CCom CCom::operator-=(CCom &com)  //���ؼ�����ֵ
  { 
    Real=Real-com.Real;            //ʵ�����
    Image=Image-com.Image;         //�鲿���
    return *this; 
  } 
  CCom CCom::operator*=(CCom &com)  //���س˷���ֵ
  { 
    double nReal=Real*com.Real-Image*com.Image;   //ʵ���˻�
    double nImage=Real*com.Image+Image*com.Real;  //�鲿�˻�
    Real=nReal; 
    Image=nImage; 
    return *this; 
  } 
  CCom CCom::operator/=(CCom &com)   //���س�����ֵ
  { 
    double nReal=(Real*com.Real+Image*com.Image)/(com.Real*com.Real+com.Image*com.Image);       //ʵ������
    double nImage=(Image*com.Real-Real*com.Image)/(com.Real*com.Real+com.Image*com.Image);      //�鲿����
    Real=nReal; 
    Image=nImage; 
    return *this; 
  } 
  int CCom::operator==(CCom &com)      //���ص���
  { 
    if(Real==com.Real && Image==com.Image) 
      return 1; 
    else 
      return 0; 
  } 

  void Test(void)            //���Ժ���
  { 
    user.nTest++; 
    cout<<"��10���⣬��100���ڵļӼ����㣬����100��:\n"; 
    double real1,real2,image1,image2,real3,real4,image3,image4; 
    CCom answer,temp; 
    int score=0; 
    char op; 
    for(int i=0;i<=9;i++)  //�������������ֵ
    {                                   
      real1=rand()%200-100; 
      image1=rand()%200-100; 
      real2=rand()%200-100; 
      image2=rand()%200-100; 
      CCom a(real1,image1),b(real2,image2); 
      real3=rand()%20-10; 
      image3=rand()%20-10; 
      real4=rand()%20-10; 
      image4=rand()%20-10; 
      CCom c(real3,image3),d(real4,image4); 
      op=rand()%3;      //��������Ӽ��˷����������ֵ
      switch(op) 
      { 
        case 0:            //��Ϊ0���Ǽӷ�
          answer=a+b; 
          cout<<a<<"����"<<b<<"����"; 
          break; 
        case 1:           //��Ϊ1���Ǽ���
          answer=a-b; 
          cout<<a<<"��ȥ"<<b<<"����"; 
          break; 
        case 2:           //��Ϊ2���ǳ˷�
          answer=c*d; 
          cout<<c<<"����"<<d<<"����"; 
          break; 
      } 
      cin>>temp;            //�����û�����ֵ
      if(answer==temp)        //�Ƚ��û�����ֵ
      { 
        score+=10;      //����ȷ���10��
      } 
      else 
      { 
        cout<<"����������\n"; 
        cout<<"��ȷ��Ϊ:"<<answer<<endl; 
      } 
    } 
    cout<<"������÷���:"<<score<<endl; 
    if(user.nTest<=3) 
    { 
      user.alAve=0; 
      user.dlScore[user.nTest-1]=score; 
      for(int i=0;i<user.nTest;i++) 
      user.alAve+=user.dlScore[i]; 
      user.alAve=user.alAve/user.nTest; 
    } 
    else 
    { 
      user.dlScore[0]=user.dlScore[1]; 
      user.dlScore[1]=user.dlScore[2]; 
      user.dlScore[2]=score; 
      for(i=0,user.alAve=0;i<3;i++) 
      user.alAve+=user.dlScore[i]; 
      user.alAve=user.alAve/3; 
    } 
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get(); 
  } 

  void Add()             //�����ӷ����㺯��
  { 
    user.nAdd++; 
    CCom num1,num2,sum,Zero(0,0); 
    cout<<"�ӷ�����\n"<<"����������������,������0����\n"; 
    cout<<"��һ������:"; 
    cin>>num1; 
    cout<<"�ڶ�������:"; 
    cin>>num2; 
    sum=num1+num2; 
    cout<<"����������:"; 
    cin>>num1; 
    int i=4; 
    while(!(num1==Zero)) 
    { 
      sum=sum+num1; 
      cout<<"��"<<i<<"������:"; 
      cin>>num1; 
      i++; 
    } 
    cout<<"�ӷ������:"<<sum<<endl; 
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get(); 
  } 

  void Sub()         //�����������㺯��
  { 
    user.nSub++; 
    CCom num1,num2,sub,Zero(0,0); 
    cout<<"������������������������0����\n"; 
    cout<<"��1������:"; 
    cin>>num1; 
    cout<<"��2������:"; 
    cin>>num2; 
    sub=num1-num2; 
    cout<<"��3������:"; 
    cin>>num1; 
    int i=4; 
    while(!(num1==Zero))  
    { 
      sub=sub-num1; 
      cout<<"��"<<i<<"������:"; 
      cin>>num1;
      i++;
    } 
    cout<<"���������:"<<sub<<endl; 
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get();
  } 

  void Mul()                     //�����˷����㺯��
  { 
    user.nMul++; 
    CCom num1,num2,mul,Zero(0,0); 
    cout<<"�˷�����\n"<<"����������������,������0����\n"; 
    cout<<"��һ������:"; 
    cin>>num1; 
    cout<<"�ڶ�������:"; 
    cin>>num2; 
    mul=num1*num2; 
    cout<<"����������:"; 
    cin>>num1; 
    int i=4; 
    while(!(num1==Zero)) 
    { 
      mul*=num1; 
      cout<<"��"<<i<<"������:"; 
      cin>>num1; 
      i++; 
    } 
    cout<<"�˷������:"<<mul<<endl; 
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get(); 
  }  

  void Div()                     //�����������㺯��
  { 
    user.nDiv++; 
    CCom num1,num2,div,Zero(0,0); 
    cout<<"��������\n"<<"����������������,������0����\n"; 
    cout<<"��һ������:"; 
    cin>>num1; 
    cout<<"�ڶ�������:"; 
    cin>>num2; 
    div=num1/num2; 
    cout<<"����������:"; 
    cin>>num1; 
    int i=4; 
    while(!(num1==Zero)) 
    { 
      div/=num1; 
      cout<<"��"<<i<<"������:"; 
      cin>>num1; 
      i++; 
    } 
    cout<<"���������:"<<div<<endl; 
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get(); 
  }  

  void Mod()           //������ģ����
  {
    CCom num,mod;
    cout<<"������һ������\n";
    cin>>num;
    mod=sqrt(num.Real*num.Real+num.Image*num.Image);
    cout<<"������ģ��:"<<mod<<endl;
    cout<<"�밴���������\n"; 
    cout.flush(); 
    cin.get(); 
    cin.get();
  }

  void Compare()                //�������ȽϺ���
  { 
    CCom num1,num2; 
    cout<<"��������������\n"; 
    cout<<"��һ������:"; 
    cin>>num1; 
    cout<<"�ڶ�������\n"; 
    cin>>num2; 
    if(num1==num2) 
      cout<<"�������������\n"; 
    else if(num1>num2) 
           cout<<num1<<"��ģ����"<<num2<<"��ģ\n"; 
         else if(num1<num2) 
                cout<<num2<<"��ģ����"<<num1<<"��ģ\n"; 
              else 
                cout<<"������������ģ���\n"; 
    cout<<"�밴���������\n"; 
    cin.get(); 
    cin.get(); 
  } 

  void userprint()         //����û���Ϣ����
  { 
    cout<<user.szName<<"ʹ�õĴ���Ϊ:"<<user.nTime<<endl; 
    cout<<"����:\t�ӷ��Ĵ���:"<<user.nAdd<<endl;
cout<<"\t�����Ĵ���:"<<user.nSub<<endl;
cout<<"\t�˷��Ĵ���:"<<user.nMul<<endl; 
    cout<<"\t���Դ���:"<<user.nTest<<"\tƽ���ɼ�:"<<user.alAve<<endl; 
  } 

  void Login()           //��ǰ�û���Ϣ����
  { 
    char szName[20]; 
    cout<<"��������������:"; 
    cin.getline(szName,20); 
    ifstream infile; 
    User user1; 
    infile.open("user.dat",ios::binary|ios::in); 
    if(!infile)       
    { 
      cout<<"û��ԭʼ��¼�ļ������ǵ�һ���û�!\n";   
      strcpy(user.szName,szName);  
      user.nTest++; 
      return; 
    } 
    infile.read((char *)&user1,sizeof(User)); 
    while(!infile.eof()) 
    { 
      if(strcmp(user1.szName,szName)==0) 
      { 
        user=user1; 
        user.nTime++; 
        cout<<"��ӭ���ٴ�ʹ�ø���������!"; 
        userprint(); 
        cin.get(); 
        infile.close(); 
        return; 
      } 
      infile.read((char *) &user1,sizeof(User)); 
    } 
    cout<<"��ӭ���ٴ�ʹ�ø���������!"; 
    strcpy(user.szName,szName); 
    user.nTime++; 
    infile.close(); 
    return; 
  } 

  void SaveFile()       //�û����ϱ��溯��
  { 
    userprint(); 
    fstream file; 
    User user1; 
    file.open("user.dat",ios::binary|ios::in|ios::out); 
    if(!file) 
    { 
      cout<<"�ļ��򿪴��󣬲��ܽ��и���!\n"; 
      return; 
    } 
    file.seekp(0,ios::beg); 
    while(!file.eof()) 
    { 
      file.read((char *)&user1,sizeof(User)); 
      if(strcmp(user1.szName,user.szName)==0) 
      { 
        file.seekp(-(sizeof(User)),ios::cur); 
        file.write((char *)&user,sizeof(User)); 
        file.close(); 
        return; 
      } 
    } 
    file.close(); 
    fstream outfile; 
    outfile.open("user.dat",ios::binary|ios::app); 
    outfile.write((char *)&user,sizeof(User)); 
    outfile.close(); 
    return; 
  } 
} 
using namespace NameCCom; 

int main(void)                   //��������ʼ
{ 
  srand(time(NULL));        //��ʼ�������"����"���
  Login();                  //��ǰ�û���Ϣ����
  char strChoise[20];       //�����ַ�����
  do 
    { 
      system("cls"); 
      cout<<"\t����һ������������������ʵ�����¹��ܣ��밴��Ӧ�İ���(0-7)\n\n\n"; 
      cout<<"\t**************************�˵�**************************\n"; 
      cout<<"\t1:�ิ���ӷ�����0����\n"; 
      cout<<"\t2:�ิ����������0����\n";         
      cout<<"\t3:�ิ���˷�����0����\n"; 
      cout<<"\t4:�ิ����������0����\n"; 
      cout<<"\t5:������ģ\n:"; 
      cout<<"\t6:�����Ƚ�\n:";
      cout<<"\t7:����100���ڵĸ����Ӽ��˷����㣬1�β���10����\n:";
      cout<<"\t0:�˳�����\n\n:"; 
      cout<<"\t����ѡ��:"; 
      cin>>strChoise; 
      if(strcmp(strChoise,"1")==0)     //�û�ѡ1�����Add()����
        Add(); 
      else if(strcmp(strChoise,"2")==0)  //�û�ѡ2�����Sub()���� 
             Sub();                              
          else if(strcmp(strChoise,"3")==0)   //�û�ѡ3�����Mul()����
                  Mul(); 
              else if(strcmp(strChoise,"4")==0)   //�û�ѡ4�����Div()����
                      Div(); 
                  else if(strcmp(strChoise,"5")==0)     //�û�ѡ5�����Mod()����
                            Mod();
                      else if(strcmp(strChoise,"6")==0)     //�û�ѡ6�����Compare()����
                            Compare(); 
                          else if(strcmp(strChoise,"7")==0)     //�û�ѡ7�����Test()����
                                 Test(); 
                              else if(strcmp(strChoise,"0")==0)  //�û�ѡ0��������ú���
                                  { 
                                    cout<<"\n\n\t��ӭ�´μ���ʹ�ø���������!\n\n"; 
                                    break; 
                                  }
                                  else 
                                  { 
                                    cout<<"\n\t��������밴���������!\n"; 
                                    cin.get(); 
                                    cin.get(); 
                                   } 
    } 
  while((strcmp(strChoise,"0")));       
    SaveFile();                     //�����û����ϱ��溯��
  return 0; 
}
