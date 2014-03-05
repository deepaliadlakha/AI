#ifndef HASH_IITB_H
#define HASH_IITB_H
#include<bitset>
#include<climits>
#include<vector>
#include<list>
using namespace std;
template <class keyType,class valueType>
class node
{
	public:
	keyType key;
	valueType value;
	int flag;
	node()
	{
		flag=0;
	}
	
	node(keyType k,valueType v)
	{
		key=k;
		value=v;
		flag=0;
	}	
};

/**
*HashIITB is a hashtable storing `key',`value' pairs as its entries.
*Hashfunction is applied to `key' entry only (i.e. `value' is payload data stored with key).
**/
template <class keyType,class valueType>
class HashIITB
{
	vector < node <keyType,valueType> > table;
	int hashkey1;
	int hashkey2;

	unsigned long int hash(const keyType& a) const
	{
		const char* beg = reinterpret_cast<const char*>(&a);
		const char* end = beg + sizeof(a);
		unsigned long int temp=0,prime=1;
		while(beg != end)
		{
		    temp=(temp+prime*(bitset<CHAR_BIT>(*beg++)).to_ulong());
			prime*=31;
		}

		return temp;
	}
 public:
	

	HashIITB()
	{
		hashkey1=101;
		hashkey2=100;
		table.resize(101);
	}
/**
*HashIITB::insert() takes two parameters, Key value `key' to be 
inserted into hash table and it's associated payload data `value'.
*It inserts this record into hashtable and returns table index where it is inserted.
**/
	int insert(keyType key,valueType value)
	{
		unsigned long int hkey=hash(key);
		int count1=1;
		int indexkey=hkey%hashkey1;
		if(table[indexkey].flag!=1)
		{
			table[indexkey].key=key;
			table[indexkey].value=value;
			table[indexkey].flag=1;
		}
		else
		{
			unsigned long int jump=(hashkey2-hkey%hashkey2);
			indexkey=(indexkey+jump)%hashkey1;
			while(table[indexkey].flag==1)
			{
				indexkey=(indexkey+jump)%hashkey1;
				count1++;
				if(count1>=hashkey1)
				break;
			}
			if(count1<hashkey1)
			{
				table[indexkey].key=key;
				table[indexkey].value=value;
				table[indexkey].flag=1;
				
			}
			else
			{
				vector < node <keyType,valueType> > temptable(table);
				table.clear();
				hashkey1=hashkey1+100;
				hashkey2=hashkey1-1;
				table.resize(hashkey1);
				for(int i=0;i<hashkey1-100;i++)
				{
					if(temptable[i].flag==1)
					insert(temptable[i].key,temptable[i].value);
				}
				temptable.clear();
				
				return insert(key,value);				
			}
		}
		return indexkey;
	}
		

/**
*HashIITB::FindFirst() needs one parameter, the `key` whose 
existence we want to find out. It must return pair<bool status,valueType val>.
*`status' indicates whether there is any element with given `key' is present
 (`true' --> an element with `key' is present. `false'-->not present)
*`val' is the FIRST inserted record's `value' component with given `key', 
if there is atleast one such record.
**/
	pair<bool,valueType> findFirst(keyType key) const
	{
		unsigned long int hkey;
		hkey = hash(key);
		int count1=1;
		int indexkey=hkey%hashkey1;
		unsigned long int jump=(hashkey2-hkey%hashkey2);
		while(table[indexkey].flag!=0)
		{
			if(table[indexkey].key==key&&table[indexkey].flag==1)
			return pair<bool,valueType>(true,table[indexkey].value);
			if(count1>=hashkey1)
			break;
			count1++;
			indexkey=(indexkey+jump)%hashkey1;
		}
		return pair<bool,valueType>(false,table[indexkey].value);
	}
/**
*Works similar to findFirst() except that it should 
return number of found records, LIST of all `value' entries 
having key value `key' instead of one. 
**/
	pair<int,list<valueType> > findAll(keyType key) const
	{
		unsigned long int hkey;
		hkey = hash(key);
		int count1=1;

		int indexkey=hkey%hashkey1;
		list<valueType> l;
		unsigned long int jump=(hashkey2-hkey%hashkey2);
		while(table[indexkey].flag!=0)
		{
			if(table[indexkey].key==key&&table[indexkey].flag==1)
			{
				l.push_back(table[indexkey].value);
			}
			if(count1>=hashkey1)
			break;
			count1++;
			indexkey=(indexkey+jump)%hashkey1;
		}
		int size1=l.size();
		return pair<int,list <valueType> >(size1,l);
	}
/**
*HashIITB::deleteFirst() accepts single parameter, the `key' 
whose corresponding record we want to delete.
*If there are 2 or more records with key value `key', you 
should delete the one that got inserted FIRST.
*It should return pair<bool status,valueType val>. Set 
`Status' to `true' if there is atleast one entry with given `key'.
*`val' is value component of deleted record (The deleted record 
should be the first one inserted into, with key value `key')
**/	
	pair<bool,valueType> deleteFirst(keyType key)
	{
		unsigned long int hkey;
		hkey = hash(key);
		int count1=1;
		int indexkey=hkey%hashkey1;
		unsigned long int jump=(hashkey2-hkey%hashkey2);
		while(table[indexkey].flag!=0)
		{
			if(table[indexkey].key==key&&table[indexkey].flag==1)
			{
				table[indexkey].flag=2;
				return pair<bool,valueType> (true,table[indexkey].value);
			}
			if(count1>=hashkey1)
			break;
			count1++;
			indexkey=(indexkey+jump)%hashkey1;
		}
		return pair<bool,valueType>(false ,table[indexkey].value);
	}

/**
*Same as deleteFirst() except that it returns  number of deleted records,
and a list of deleted `values' instead of one deleted value.
**/
	pair<int,list<valueType> > deleteAll(keyType key)
	{
		unsigned long int hkey;
		hkey = hash(key);
		int count1=1;
		int indexkey=hkey%hashkey1;
		list<valueType> l;
		unsigned long int jump=(hashkey2-hkey%hashkey2);
		while(table[indexkey].flag!=0)
		{
			if(table[indexkey].key==key&&table[indexkey].flag==1)
			{
				l.push_back(table[indexkey].value);
				table[indexkey].flag=2;
			}
			if(count1>=hashkey1)
			break;
			count1++;
			indexkey=(indexkey+jump)%hashkey1;
		}
		int size1=l.size();
		return pair<int,list <valueType> >(size1,l);
	}

/**
*HashIITB::size() returns the number of records stored in hashtable at present.
**/
	int size(void) const
	{
		int s=0;
		for(int i=0;i<hashkey1;i++)
		{
			if(table[i].flag==1)
			s++;
		}
		return s;
	}
	
/**
*HashIITB::tableSize() returns the size of the hash table array.
**/
	int tableSize(void) const
	{
		return hashkey1;
	} 
};


#endif
