#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
	double coeff;
	int pow;
	struct Node * next;
} NODE;

NODE* createNode ()
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->coeff = 0;
	temp->pow = 0;
	temp->next = NULL;
	return temp;
}

void insert (NODE *list, double coeff, int pow)
{
	NODE *temp = createNode();
	NODE *p;
	
	temp->coeff = coeff;
	temp->pow = pow;
	temp->next = NULL;
	
	if (list->next == NULL)
		list->next = temp;
	
	else
	{
		p = list->next;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
		
	}
}

int addToPolynomialTerm (NODE *polyn, int pow, double coeff)
{
	NODE *temp = polyn->next;
	while (temp != NULL)
	{
		if (temp->pow == pow)
		{
			temp->coeff += coeff;
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void inputPolynomial (NODE *polynomial, char *id)
{
	
	int i, n;
	double coeff;
	int pow;
	printf("Enter number of terms in '%s'\n", id);
	scanf("%d", &n);	
	for (i = 0; i < n; ++i)
	{
		printf("Enter coefficient (can be float) and power (integer only) of %d\n", (i+1));
		scanf("%lf %d", &coeff, &pow);
		if ((addToPolynomialTerm(polynomial, pow, coeff)) == 0)
			insert(polynomial, coeff, pow);
	}	
}

NODE* createPolynomial (char *id)
{
	NODE *polyn = createNode();
	inputPolynomial(polyn, id);
	return polyn;
}

NODE* addSubtractPolynomials (NODE *polya, NODE *polyb, int choice)
{
	NODE *polyc = createNode();	
	NODE *tempa = polya->next;
	NODE *tempb = polyb->next;
	
	while (tempa != NULL)
	{
		if ((addToPolynomialTerm(polyc, tempa->pow, tempa->coeff)) == 0)
			insert(polyc, tempa->coeff, tempa->pow);
		tempa = tempa->next;
	}
	while (tempb != NULL)
	{
		if ((addToPolynomialTerm(polyc, tempb->pow, choice*tempb->coeff)) == 0)
			insert(polyc, choice*tempb->coeff, tempb->pow);
		tempb = tempb->next;
	}
	
	return polyc;
}

NODE* add (NODE *polya, NODE *polyb)
{
	NODE *polyc = createNode();
	polyc = addSubtractPolynomials(polya, polyb, 1);
	return polyc;
}

NODE* subtract (NODE *polya, NODE *polyb)
{
	NODE *polyc = createNode();
	polyc = addSubtractPolynomials(polya, polyb, -1);
	return polyc;
}

NODE* multiply (NODE *polya, NODE *polyb)
{
	NODE *polyc = createNode();	
	NODE *tempa = polya->next;	
	while (tempa != NULL)
	{
		NODE *tempb = polyb->next;
		while (tempb != NULL)
		{
			if ((addToPolynomialTerm(polyc, tempa->pow + tempb->pow, tempa->coeff * tempb->coeff)) == 0)
				insert(polyc, tempa->coeff * tempb->coeff, tempa->pow + tempb->pow);
			tempb = tempb->next;
		}
		tempa = tempa->next;
	}	
	return polyc;
}

void display (NODE *polyn)
{
	
	NODE *temp = polyn->next;	
	int isCoeffNonFloat = ((temp->coeff) == (int)(temp->coeff))?1:0;	
	if (temp == NULL)
	{
		printf("0 ");
		return;
	}	
	if (temp->coeff == 1) printf("x");
	else if (temp->coeff == 0) printf("0");
	else if (temp->coeff == -1) printf("-x");
	else
	{
		if (isCoeffNonFloat)
			printf("%.0lfx", temp->coeff);
		else
			printf("%.2lfx", temp->coeff);
	}	
	if (temp->pow == 0 || temp->coeff == 0) printf(" ");
	else if (temp->pow != 1)
	{
	        printf("^%d", temp->pow);
	}	
	temp = temp->next;	
	while (temp != NULL)
	{
		
		isCoeffNonFloat = ((temp->coeff) == (int)(temp->coeff))?1:0;		
		if (temp->coeff == 0)
		{
			temp = temp->next;
			continue;
		}		
		if (temp->coeff == 1) printf("+x");
		else if (temp->coeff == -1) printf("-x");
		else
		{
			if (isCoeffNonFloat)
				printf("%s%.0lfx", (temp->coeff > 0)?" + ":" ", temp->coeff);
			else
				printf("%s%.2lfx", (temp->coeff > 0)?" + ":" ", temp->coeff);
		}		
		if (temp->pow == 0) printf(" ");
		else if (temp->pow != 1)
		{
		        printf("^%d", temp->pow);
		}		
		temp = temp->next;
	}
	printf("\n");
}

int main ()
{	
        char choice, c1;	
	do
	{
		NODE *a = createPolynomial("A");
		NODE *b = createPolynomial("B");		
		NODE *c;
		char *opid;
		printf("1 to add, 2 to subtract, 3 to multiply\n");
		scanf(" %c", &choice);
		if (choice == '1')
		{
			c = add(a, b);
			opid = "+";
		}
		else if (choice == '2')
		{
			c = subtract(a, b);
			opid = "-";
		}
		else if (choice == '3')
		{
			c = multiply(a, b);
			opid = "*";
		}
		printf("A = ");
		display(a);
		printf("B = ");
		display(b);		
		printf("A %s B = ", opid);
		display(c);
		printf("Go again? y/n?\n");
		scanf(" %c", &c1);
	} while (c1 == 'y');		
	return 0;
}

