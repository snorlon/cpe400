struct ips 
{
int that[4];
ips* next;
};

class IpCreate
      {
	  public:
        IpCreate();
        ~IpCreate();
        void MakeEmpty();
        bool IsEmpty() const;
        bool IsFull() const;
		bool compareIP(int*,int*);
		void compareList(int*);
		void assignIP(int*);
        int* Generate();
		int* create();
		ips* header;
		ips* current;
      };


IpCreate::IpCreate()
  {
  
  header=NULL;
  current=header;
  }

IpCreate::~IpCreate()
  {
  MakeEmpty();
  }


void IpCreate::MakeEmpty()
  {

  }

bool IpCreate::IsEmpty() const
     {
		return false;
     }


bool IpCreate::IsFull() const
     {
		return false;
     }

int* IpCreate::Generate() 
{
	int* ip;
	ip=create();
	if (header==NULL)
	{
		header=new ips;
		current=header;
		assignIP(ip);
		header->next=NULL;
		return header->that;
	}
	else
	{
		current=current->next;
		current=new ips;
		compareList(ip);
		assignIP(ip);
		current->next=NULL;
		return current->that;
	}
}
int* IpCreate::create()
{
	//int* ipstack=new int [4];
	int* input=new int [4];
	for(int i=0;i<4;i++)
	{
	input[i] = rand() % 256;
	}
	return input;

}
void IpCreate::assignIP(int* val)
{
	for(int i=0; i<4;i++)
	{
	current->that[i]=val[i];
	}
}

bool IpCreate::compareIP(int* ip1,int*ip2)
{
	int check=0;

	for(int i=0;i<4;i++)
	{
		if(ip1==ip2)
		{
			check+=1;
		}
	}
	if(check<4)
	{
	return true;
	}
	else
	{
		return false;
	}
}
void IpCreate::compareList(int*begin)
{
	ips* nav;
	nav=header;

	while(nav!=NULL)
	{
		if(compareIP(begin,nav->that))
		{
			nav=nav->next;
		}
		else
		{
			assignIP(begin);
			nav=header;
		}
	}

}