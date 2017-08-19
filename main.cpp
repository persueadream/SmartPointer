
//	智能指针管理 


#include <iostream.h>

class U_Ptr{
	public:
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int *p):ip(p), use(1)
	{
				
	}
	~U_Ptr() {
		delete ip;
	}
};

class HasPtr{
	public:
		HasPtr(int *p, int i):ptr(new U_Ptr(p)), val(i){
			
		}	
		HasPtr(const HasPtr &orig):
			ptr(orig.ptr), val(orig.val){
				++ptr->use;
			}
		HasPtr& operator=(const HasPtr&);
		~HasPtr(){
			if(--ptr->use == 0)
				delete ptr;
		}
	public:
		U_Ptr *ptr;
		int val;
	public:
		int *get_ptr() const {
			return ptr->ip;
		}
		int get_int() const {
			return val;
		}
		void set_ptr(int *p) {
			ptr->ip = p;  
		} 
		void set_int(int i) {
			val = i;
		}
		
		int get_ptr_val() const {
			return *ptr->ip;
		}
		
		int set_ptr_val(int i) {
			*ptr->ip = i;
		} 
		
};


HasPtr& HasPtr::operator= (const HasPtr &rhs)
{
	++rhs.ptr->use;
	if(--ptr->use == 0)
	{
		delete ptr;
	}
	ptr = rhs.ptr;
	val = rhs.val;
	
	return *this;
}

int main(int argc, char *argv[])
{
	int *p = new int(20), h = 30;
	HasPtr a(p, 20);
	cout << "Object a:" << endl;
	cout << "use = " << a.ptr->use << endl;
	cout << "*ip = " << *(a.ptr->ip) << endl;
	cout << "val = " << a.val << endl;
	
	HasPtr b(&h, 50);
	cout << "Object b:" << endl;
	cout << "use = " << b.ptr->use << endl;
	cout << "*ip = " << *(b.ptr->ip) << endl;
	cout << "val = " << b.val << endl;
	
	b = a;
	cout << "Object a:" << endl;
	cout << "use = " << a.ptr->use << endl;
	cout << "*ip = " << *(a.ptr->ip) << endl;
	cout << "val = " << a.val << endl;
	
	
	cout << "Object b:" << endl;
	cout << "use = " << b.ptr->use << endl;
	cout << "*ip = " << *(b.ptr->ip) << endl;
	cout << "val = " << b.val << endl;
	
//	delete p;
	
	HasPtr c(b);
	cout << "delete p:" << endl;
	cout << "use = " << c.ptr->use << endl;
	cout << "*ip = " << *(c.ptr->ip) << endl;
	cout << "val = " << c.val << endl;
	
	
	return 0;
}
