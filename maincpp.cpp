#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>

using namespace std;


enum
{
	black = 1,
	white = 2,



};
enum
{
	empty,
	Wpawn,
	Wknight,
	Wbishop,
	Wrook,
	Wqueen,
	Wking,
	Bpawn,
	Bknight,
	Bbishop,
	Brook,
	Bqueen,
	Bking,
};


inline void unitplace(unsigned __int64 d[], int type, int location)
{
	d[location] = d[location] - ((d[location] << 60) >> 60) + type;


//	d[location] = d[location] - ((d[location]))

}

inline int getunit(unsigned __int64 d[], int location)
{

	return((d[location] << 60) >> 60);
}

inline int converter(int x, int y)
{
	return x+y*8;
}

inline void display(unsigned __int64 d[])
{

	for (int j=0;j<8;j++)
	{
		for (int i=0;i<8;i++)
		{
			switch (getunit(d, converter(i, j)))
			{
				case Wpawn:

					cout << char('P');

				break;
				case Wknight:

					cout << char('N');
					break;

				case Wbishop:

					cout << char('B');
					break;

				case Wrook:

					cout << char('R');
					break;

				case Wqueen:

					cout << char('Q');
					break;

				case Wking:

					cout << char('K');
					break;

				case Bpawn:

					cout << char('p');
					break;
				case Bknight:

					cout << char('n');
					break;

				case Bbishop:

					cout << char('b');
					break;

				case Brook:

					cout << char('r');
					break;

				case Bqueen:

					cout << char('q');
					break;

				case Bking:

					cout << char('k');
					break;

				default:
					cout << char(95);

				
			}
		}
		cout << endl;
	}


}

inline bool onmap(int x, int y)
{
	if (x>7||x<0||y>7||y<0)
	{
		return false;
	}
	return true;
}

inline int colorcheck(unsigned __int64 d[], int location)
{
	if (!(getunit(d, location)))
	{
		return 0;
	}
	else if (getunit(d, location)<7)
	{
		return 1;
	}
	else
	{
		return 2;

	}


}

inline vector<int> pawnrule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(32);
	int counter = 1;
	if (getunit(d,location) == Wpawn)
	{
		if (((d[location] << 59) >> 63) && (!getunit(d, location + 16)) && (!getunit(d, location + 8)))
		{
			
			possiblemoves[counter] = location + 8;
			counter++;
			possiblemoves[counter] = location + 16;
			counter++;
			d[location] -= 16;
		}
		else if (!getunit(d, location + 8))
		{
			
			possiblemoves[counter] = location + 8;
			counter++;
			
		}
		if ((colorcheck(d, location - 1 + 8) != colorcheck(d, location)) && getunit(d, location - 1 + 8) && (((location - 1 + 8) % 8) != 7))
		{
			possiblemoves[counter] = location - 1 + 8;
			counter++;
		}
		if (colorcheck(d, location + 1 + 8) != colorcheck(d, location) && getunit(d, location + 1 + 8) && (((location - 1 + 8) % 8) != 0))
		{
			possiblemoves[counter] = location + 1 + 8;
			counter++;
		}
	}
	else
	{
		if (((d[location] << 59) >> 63) && (!(getunit(d, location - 16))) && (!getunit(d, location - 8)))
		{
			possiblemoves[counter] = location - 16;
			counter++;
			possiblemoves[counter] = location - 8;
			counter++;
			d[location] -= 16;

		}
		else if (!getunit(d, location - 8))
		{
			possiblemoves[counter] = location - 8;
			counter++;
		}
		if ((colorcheck(d, location - 1 - 8) != colorcheck(d, location)) && getunit(d, location - 1 - 8) && (((location - 1 + 8) % 8) != 7))
		{
			possiblemoves[counter] = location - 1 - 8;
			counter++;
		}
		if ((colorcheck(d, location + 1 - 8) != colorcheck(d, location)) && getunit(d, location + 1 - 8) && (((location - 1 + 8) % 8) != 0))
		{
			possiblemoves[counter] = location + 1 - 8;
			counter++;
		}
	}

	possiblemoves[0] = counter-1;

	return possiblemoves;
}

inline vector<int> knightrule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(10);
	int counter=1;

	if ((colorcheck(d, location + 2 * 8 + 1) != colorcheck(d, location)) && ((location + 2 * 8 + 1) <= (63)) && (((location + 2 * 8 + 1) % 8) != 0))
	{ 
		possiblemoves[counter] = location + 2 * 8 + 1;
		counter++;
	}
	if ((colorcheck(d, location + 2 * 8 - 1) != colorcheck(d, location)) && ((location + 2 * 8 - 1) <= (63)) && (((location + 2 * 8 - 1) % 8) != 7))
	{
		possiblemoves[counter] = location + 2 * 8 - 1;
		counter++;
	}
	if ((colorcheck(d, location - 2 * 8 + 1) != colorcheck(d, location)) && ((location - 2 * 8 + 1) >= 0) && (((location - 2 * 8 + 1) % 8) != 0))
	{
		possiblemoves[counter] = location - 2 * 8 + 1;
		counter++;
	}
	if ((colorcheck(d, location - 2 * 8 - 1) != colorcheck(d, location)) && ((location - 2 * 8 - 1) >= 0) && (((location - 2 * 8 - 1) % 8) != 7))
	{
		possiblemoves[counter] = location - 2 * 8 - 1;
		counter++;
	}
	if ((colorcheck(d, location + 8 + 2) != colorcheck(d, location)) && ((location + 8 + 2) <= 63) && (((location + 8 + 2) % 8) != 0) && (((location + 8 + 2) % 8) != 1))
	{
		possiblemoves[counter] = location + 8 + 2;
		counter++;
	}
	if ((colorcheck(d, location + 8 - 2) != colorcheck(d, location)) && ((location + 8 - 2) <= 63) && (((location + 8 - 2) % 8) != 7) && (((location + 8 - 2) % 8) != 6))
	{
		possiblemoves[counter] = location + 8 - 2;
		counter++;
	}
	if ((colorcheck(d, location - 8 + 2) != colorcheck(d, location)) && ((location - 8 + 2) >= 0) && (((location - 8 + 2) % 8) != 0) && (((location - 8 + 2) % 8) != 1))
	{
		possiblemoves[counter] = location - 8 + 2;
		counter++;
	}
	if ((colorcheck(d, location - 8 - 2) != colorcheck(d, location)) && ((location - 8 - 2) >= 0) && (((location - 8 - 2) % 8) != 7) && (((location - 8 - 2) % 8) != 6))
	{
		possiblemoves[counter] = location - 8 - 2;
		counter++;
	}
	
	possiblemoves[0] = counter - 1;

	return possiblemoves;
}

inline vector<int> bishoprule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(32);
	int counter = 1;
	int i;

	for (i = 1; (!getunit(d, location + i + 8 * i)) && ((location + i + 8 * i)<=63) && (((location + i + 8 * i)%8)!=0); i++, counter++)
	{
		possiblemoves[counter] = location + i + 8 * i;
	}
	if ((getunit(d, location + i + 8 * i)) && (colorcheck(d, location + i + 8 * i) != colorcheck(d, location)) && (((location + i + 8 * i) % 8) != 0) && ((location + i + 8 * i) <= 63))
	{
		possiblemoves[counter] = location + i + 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i + 8 * i)) && ((location - i + 8 * i)<=63) && (((location - i + 8 * i)%8)!=7); i++, counter++)
	{
		possiblemoves[counter] = location - i + 8 * i;

	}
	if ((getunit(d, location - i + 8 * i)) && (colorcheck(d, location - i + 8 * i) != colorcheck(d, location)) && (((location - i + 8 * i) % 8) != 7) && ((location - i + 8 * i) <= 63))
	{
		possiblemoves[counter] = location - i + 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location + i - 8 * i)) && ((location + i - 8 * i)>=0) && (((location + i - 8 * i)%8)!=0); i++, counter++)
	{
		possiblemoves[counter] = location + i - 8 * i;
	}
	if ((getunit(d, location + i - 8 * i)) && (colorcheck(d, location + i - 8 * i) != colorcheck(d, location)) && (((location + i - 8 * i) % 8) != 0) && ((location + i - 8 * i) >= 0))
	{
		possiblemoves[counter] = location + i - 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i - 8 * i)) && ((location - i - 8 * i)>=0) && (((location - i - 8 * i)%8)!=7); i++, counter++)
	{
		
		possiblemoves[counter] = location - i - 8 * i;
	}
	if ((getunit(d, location - i - 8 * i)) && (colorcheck(d, location - i - 8 * i) != colorcheck(d, location)) && (((location - i - 8 * i) % 8) != 7) && ((location - i - 8 * i) >= 0))
	{
		possiblemoves[counter] = location - i - 8 * i;
		counter++;
	}

	possiblemoves[0] = counter - 1;

	return possiblemoves;
}

inline vector<int> rookrule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(32);
	int counter = 1;
	int i;

	for (i = 1; (!getunit(d, location + i * 8)) && ((location + i * 8)<=63); counter++, i++)
	{
		possiblemoves[counter]=location + i * 8;
	}
	if ((getunit(d, location + i * 8)) && (colorcheck(d, location + i * 8) != colorcheck(d, location)) && ((location + i * 8) <= 63))
	{
		possiblemoves[counter] = location + i * 8;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i * 8)) && ((location - i * 8)>=0); counter++, i++)
	{
		possiblemoves[counter] = location - i * 8;
	}
	if ((getunit(d, location - i * 8)) && (colorcheck(d, location - i * 8) != colorcheck(d, location)) && ((location - i * 8) >= 0))
	{
		possiblemoves[counter] = location - i * 8;
		counter++;
	}

	for (i = 1; (!getunit(d, location + i)) && (((location + i)%8)!=0); counter++, i++)
	{
		possiblemoves[counter] = location + i;
	}
	if ((getunit(d, location + i)) && (colorcheck(d, location + i) != colorcheck(d, location)) && (((location + i) % 8) != 0))
	{
		possiblemoves[counter] = location + i;
		counter++;
	}


	for (i = 1; (!getunit(d, location - i)) && (((location - i)%8)!=7); counter++,i++)
	{
		possiblemoves[counter] = location - i;
	}
	if ((getunit(d, location - i)) && (colorcheck(d, location - i) != colorcheck(d, location)) && (((location - i) % 8) != 7) && ((location - i)>=0))
	{
		possiblemoves[counter] = location - i;
		counter++;
	}

	possiblemoves[0] = counter-1;

	return possiblemoves;
}

inline vector<int> queenrule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(32);
	int counter = 1;
	int i;

	for (i = 1; (!getunit(d, location + i * 8)) && ((location + i * 8) <= 63); counter++, i++)
	{
		possiblemoves[counter] = location + i * 8;
	}
	if ((getunit(d, location + i * 8)) && (colorcheck(d, location + i * 8) != colorcheck(d, location)) && ((location + i * 8) <= 63))
	{
		possiblemoves[counter] = location + i * 8;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i * 8)) && ((location - i * 8) >= 0); counter++, i++)
	{
		possiblemoves[counter] = location - i * 8;
	}
	if ((getunit(d, location - i * 8)) && (colorcheck(d, location - i * 8) != colorcheck(d, location)) && ((location - i * 8) >= 0))
	{
		possiblemoves[counter] = location - i * 8;
		counter++;
	}

	for (i = 1; (!getunit(d, location + i)) && (((location + i) % 8) != 0); counter++, i++)
	{
		possiblemoves[counter] = location + i;
	}
	if ((getunit(d, location + i)) && (colorcheck(d, location + i) != colorcheck(d, location)) && (((location + i) % 8) != 0))
	{
		possiblemoves[counter] = location + i;
		counter++;
	}


	for (i = 1; (!getunit(d, location - i)) && (((location - i) % 8) != 7); counter++, i++)
	{
		possiblemoves[counter] = location - i;
	}
	if ((getunit(d, location - i)) && (colorcheck(d, location - i) != colorcheck(d, location)) && (((location - i) % 8) != 7) && ((location - i) >= 0))
	{
		possiblemoves[counter] = location - i;
		counter++;
	}
	for (i = 1; (!getunit(d, location + i + 8 * i)) && ((location + i + 8 * i) <= 63) && (((location + i + 8 * i) % 8) != 0); i++, counter++)
	{
		possiblemoves[counter] = location + i + 8 * i;
	}
	if ((getunit(d, location + i + 8 * i)) && (colorcheck(d, location + i + 8 * i) != colorcheck(d, location)) && (((location + i + 8 * i) % 8) != 0) && ((location + i + 8 * i) <= 63))
	{
		possiblemoves[counter] = location + i + 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i + 8 * i)) && ((location - i + 8 * i) <= 63) && (((location - i + 8 * i) % 8) != 7); i++, counter++)
	{
		possiblemoves[counter] = location - i + 8 * i;

	}
	if ((getunit(d, location - i + 8 * i)) && (colorcheck(d, location - i + 8 * i) != colorcheck(d, location)) && (((location - i + 8 * i) % 8) != 7) && ((location - i + 8 * i) <= 63))
	{
		possiblemoves[counter] = location - i + 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location + i - 8 * i)) && ((location + i - 8 * i) >= 0) && (((location + i - 8 * i) % 8) != 0); i++, counter++)
	{
		possiblemoves[counter] = location + i - 8 * i;
	}
	if ((getunit(d, location + i - 8 * i)) && (colorcheck(d, location + i - 8 * i) != colorcheck(d, location)) && (((location + i - 8 * i) % 8) != 0) && ((location + i - 8 * i) >= 0))
	{
		possiblemoves[counter] = location + i - 8 * i;
		counter++;
	}

	for (i = 1; (!getunit(d, location - i - 8 * i)) && ((location - i - 8 * i) >= 0) && (((location - i - 8 * i) % 8) != 7); i++, counter++)
	{

		possiblemoves[counter] = location - i - 8 * i;
	}
	if ((getunit(d, location - i - 8 * i)) && (colorcheck(d, location - i - 8 * i) != colorcheck(d, location)) && (((location - i - 8 * i) % 8) != 7) && ((location - i - 8 * i) >= 0))
	{
		possiblemoves[counter] = location - i - 8 * i;
		counter++;
	}


	possiblemoves[0] = counter - 1;
	return possiblemoves;
}

inline vector<int> kingrule(unsigned __int64 d[], int location)
{
	vector<int> possiblemoves;
	possiblemoves.resize(12);
	int counter = 1;
	if ((!getunit(d, location + 8)) && ((location + 8)<=(63)))
	{
		possiblemoves[counter] = location + 8;
		counter++;
	}
	if ((!getunit(d, location - 8)) && ((location - 8)>=(0)))
	{
		possiblemoves[counter] = location - 8;
		counter++;
	}
	if ((!getunit(d, location + 1)) &&(((location + 1) % 8) != 0))
	{
		possiblemoves[counter] = location + 1;
		counter++;
	}
	if ((!getunit(d, location - 1)) && (((location - 1) % 8) != 7))
	{
		possiblemoves[counter] = location - 1;
		counter++;
	}
	if ((!getunit(d, location + 8+1)) && ((location + 8+1)<=(63)) && (((location + 8+1) % 8) != 0))
	{
		possiblemoves[counter] = location + 8 + 1;
		counter++;
	}
	if ((!getunit(d, location + 8 - 1)) && ((location + 8 - 1)<=(63)) && (((location + 8 - 1) % 8) != 7))
	{
		possiblemoves[counter] = location + 8 - 1;
		counter++;
	}
	if ((!getunit(d, location - 8 + 1)) && ((location - 8 + 1)>=(0)) && (((location - 8 + 1) % 8) != 0))
	{
		possiblemoves[counter] = location - 8 + 1;
		counter++;
	}
	possiblemoves[0] = counter - 1;
	return possiblemoves;
}

inline void move(unsigned __int64 d[], int newlocation,int originallocation)
{
	int UNIT = getunit(d, originallocation);
	unitplace(d, empty, originallocation);
	unitplace(d, UNIT, newlocation);
}



inline void randommove(unsigned __int64 d[], int color)
{
	vector<int> possiblemoves;
	possiblemoves.resize(32);
	int p;
	int t;
	for (t = rand() % 32; possiblemoves[0] == 0;)
	{
		for (p = rand() % 64; colorcheck(d, p) != color; p = rand() % 64)
		{
		}


		
		if (getunit(d, p) == 1 || getunit(d, p) == 7)
		{
			possiblemoves = pawnrule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(t % possiblemoves[0]) + 1], p);
				if ((possiblemoves[(t%possiblemoves[0]) + 1] > 55))
				{ 
					unitplace(d, (rand() % 4) + 2, possiblemoves[(t%possiblemoves[0])+1]);
				}
				else if ((possiblemoves[(t%possiblemoves[0]) + 1] < 8))
				{
					unitplace(d, (rand() % 4) + 8, possiblemoves[(t%possiblemoves[0])+1]);
				}
			}
		}
		else if (getunit(d, p) == 2 || getunit(d, p) == 8)
		{
			possiblemoves = knightrule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(rand() % possiblemoves[0]) + 1], p);
			}
		}
		else if (getunit(d, p) == 3 || getunit(d, p) == 9)
		{
			possiblemoves = bishoprule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(rand() % possiblemoves[0]) + 1], p);
			}
		}
		else if (getunit(d, p) == 4 || getunit(d, p) == 10)
		{
			possiblemoves = rookrule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(rand() % possiblemoves[0]) + 1], p);
			}
		}
		else if (getunit(d, p) == 5 || getunit(d, p) == 11)
		{
			possiblemoves = queenrule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(rand() % possiblemoves[0]) + 1], p);
			}
		}
		else if (getunit(d, p) == 6 || getunit(d, p) == 12)
		{
			possiblemoves = kingrule(d, p);
			if (possiblemoves[0] > 0)
			{
				move(d, possiblemoves[(rand() % possiblemoves[0]) + 1], p);
			}
		}
	}
	
}



int main()
{
	int whosturn = true;

	srand(time(0));


	unsigned __int64 d[64];

	for (int i=0;i<64;i++)
	{
		d[i] = 0;
	}



	for (int i = 0; i < 8; i++)
	{
		d[converter(i, 1)] = 16;
		unitplace(d, Wpawn, converter(i, 1));
		
	}
	for (int i = 0; i < 8; i++)
	{
		d[converter(i, 6)]=16;
		unitplace(d, Bpawn, converter(i, 6));

	}


	d[converter(0, 0)] = 16;
	unitplace(d, Wrook, converter(0, 0));
	d[converter(7, 0)] = 16;
	unitplace(d, Wrook, converter(7, 0));
	d[converter(0, 7)] = 16;
	unitplace(d, Brook, converter(0, 7));
	d[converter(7, 7)] = 16;
	unitplace(d, Brook, converter(7, 7));

	unitplace(d, Wbishop, converter(2, 0));
	unitplace(d, Wbishop, converter(5, 0));
	unitplace(d, Bbishop, converter(2, 7));
	unitplace(d, Bbishop, converter(5, 7));

	unitplace(d, Wknight, converter(1, 0));
	unitplace(d, Wknight, converter(6, 0));
	unitplace(d, Bknight, converter(1, 7));
	unitplace(d, Bknight, converter(6, 7));

	unitplace(d, Wqueen, converter(4, 0));
	unitplace(d, Bqueen, converter(4, 7));

	d[converter(3, 0)] = 16;
	unitplace(d, Wking, converter(3, 0));
	d[converter(3, 7)] = 16;
	unitplace(d, Bking, converter(3, 7));

	int dummy1 = 1;
	int dummy2 = 1;
	int numberofmoves=1;
	for (; dummy1&&dummy2; numberofmoves++)
	{
		randommove(d, whosturn);
		if (whosturn == 1)
		{
			whosturn = 2;
		}
		else
		{
			whosturn = 1;
		}
		dummy1 = 0;
		dummy2 = 0;
		for (int i = 0; i < 64; i++)
		{
			if (getunit(d, i) == Wking)
			{
				dummy1 = 1;
			}
			if (getunit(d, i) == Bking)
			{
				dummy2 = 1;
			}
		}

		display(d);
		Sleep(3000);
		std::system("cls");
	}

	if (dummy1==0)
	{ 
		std::cout << "black won" << std::endl;
	}
	if (dummy2 == 0)
	{
		std::cout << "white won" << std::endl;
	}
	display(d);

	std::cout << "number of moves is :" << numberofmoves << endl;

/*	move(d, pawnrule(d, converter(0, 6))[rand()%2+1] , converter(0, 6));
	move(d, rookrule(d, converter(0, 7))[1], converter(0, 7));
	move(d, knightrule(d, converter(6, 7))[0], converter(6, 7));
	move(d, bishoprule(d, converter(6, 3))[0], converter(6, 3));*/


/*	cout << converter(0, 5) << endl;
	cout << pawnrule(d, converter(0, 6))[1] << endl;*/


//	pawnrule(d, converter(0, 6))[rand()%2];

	




	
	cin.get();
	cin.get();
}




