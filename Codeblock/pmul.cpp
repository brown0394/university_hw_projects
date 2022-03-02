#include <iostream>
#include <cstring>
#include <cstdio>

#define MAX 1000
using namespace std;

class Polynomial
{
public:
	Polynomial()
	{
		num = 0;
		exp = 0;
	}

    void SetPoly(int p_n, int p_ex)
	{
		num = p_n;
		exp = p_ex;
	}

	bool AddPoly(const Polynomial& other)
	{
	    if(exp == other.exp)
        {
            num += other.num;
            return 1;
        }
        return 0;
	}

	void PrintPoly()
	{
	    printf("%d %d", num, exp);
	}

	bool Iszero()
	{
	    if(num == 0)
        {
            return true;
        }
        return false;
	}

	const Polynomial operator *(const Polynomial& other)
	{
	    Polynomial result;

        if(num != 0 && other.num != 0)
        {
            result.num = num * other.num;
        }
        else
        {
            result.num = 0;
        }

        result.exp = exp + other.exp;
        return result;
	}

    const Polynomial operator =(const Polynomial& other)
	{
	    num = other.num;
	    exp = other.exp;
	}

	private:
		int num;
		int exp;

};

int main()
{
	char input[MAX] = { "\0" };
    char input2[MAX] = { "\0" };

	cin.getline(input, MAX);
	cin.getline(input2, MAX);

	const int index = input[0] - '0';
	const int index2 = input2[0] - '0';
	Polynomial poly[index];
	Polynomial poly2[index2];
    int polycount = 0;
	int num = 0;
	int exp = 0;
	bool space = false;
    Polynomial result[index * index2];
	int residxcount = 0;
    bool Isminus = false;
    int numcount = 0;


	for (int i = 2; i < strlen(input); ++i)
	{
	    if(input[i] == '-')
        {
            Isminus = true;
            continue;
        }
	    if(input[i] == ' ')
        {
            if(space == false)
            {
                space = true;
            }
            else
            {
                space = false;
            }
        }
        else
        {
            if(space == false)
            {
                if(i + 1 < strlen(input) && input[i + 1] != ' ')
                {
                    num = (input[i] - '0') * 10 + (input[i+1] - '0');
                    ++i;
                }
                else
                    num = input[i] - '0';
                if(Isminus)
                {
                    Isminus = false;
                    num *= -1;
                }
            }
            else
            {
                if(i + 1 < strlen(input) && input[i + 1] != ' ')
                {
                    exp = (input[i] - '0') * 10 + (input[i+1] - '0');
                    ++i;
                }
                else
                    exp = input[i] - '0';
                if(Isminus)
                {
                    Isminus = false;
                    exp *= -1;
                }
                poly[polycount++].SetPoly(num, exp);
            }
        }
	}

    polycount = 0;
    space = false;

	for (int i = 2; i < strlen(input2); ++i)
	{
	    if(input2[i] == '-')
        {
            Isminus = true;
            continue;
        }
	    if(input2[i] == ' ')
        {
            if(space == false)
            {
                space = true;
            }
            else
            {
                space = false;
            }
        }
        else
        {
            if(space == false)
            {
                if(i + 1 < strlen(input2) && input2[i + 1] != ' ')
                {
                    num = (input2[i] - '0') * 10 + (input2[i+1] - '0');
                    ++i;
                }
                else
                    num = input2[i] - '0';
                if(Isminus)
                {
                    Isminus = false;
                    num *= -1;
                }
            }
            else
            {
                if(i + 1 < strlen(input2) && input2[i + 1] != ' ')
                {
                    exp = (input2[i] - '0') * 10 + (input2[i+1] - '0');
                    ++i;
                }
                else
                    exp = input2[i] - '0';
                if(Isminus)
                {
                    Isminus = false;
                    exp *= -1;
                }
                poly2[polycount++].SetPoly(num, exp);
            }
        }
	}




	for(int i = 0; i < index; ++i)
    {
        for(int j = 0; j < index2; ++j)
        {
            result[residxcount++] = poly[i] * poly2[j];
        }
    }

    for(int i = 0; i < residxcount; ++i)
    {
        for(int j = i + 1; j < residxcount; ++j)
        {
            if(result[i].AddPoly(result[j]) == true)
            {
                result[j].SetPoly(0, 0);
            }
        }
    }

    for(int i = 0; i < residxcount; ++i)
    {
        if(result[i].Iszero() == false)
            ++numcount;
    }

    cout << numcount << ' ';

    for(int i = 0; i < residxcount; ++i)
    {
        if(result[i].Iszero() == false)
        {
            if(i > 0)
            {
                putchar(' ');
            }
            result[i].PrintPoly();
        }
    }

	return 0;
}
