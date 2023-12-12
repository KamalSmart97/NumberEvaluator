//code to find the combination of the operator used along with the user given input to get the desired result.

#include<iostream>

using namespace std;

static int nIndex = 0;
unsigned int factorial(unsigned int n)
{
	if (n == 0 || n == 1)
		return 1;
	return n * factorial(n - 1);
}

int swap(char* character, int nNoOfCharacter)
{
	char a[1] = "";

	for(int i=0;i<(nNoOfCharacter-1);i++)
	{
		a[0] = character[i];
		character[i] = character[i + 1];
		character[i + 1] = a[0];
	}
	return 0;
}

int evaluateString(int num1, int num2, char* operatr)
{
	const char cTemp = operatr[0];
	if (cTemp == '*')
		return num1 * num2;	
	else if (cTemp == '/')
		return num1 / num2;	
	else if (cTemp == '+')
		return num1 + num2;
	else if (cTemp == '-')
		return num1 - num2;

	return 0;
}


int evaluateExpression(char* operators, int* nNumbers, int nNoOfNumbers, int* nResultValue)
{
	if (nNoOfNumbers > 2)
	{
		int i = 0, nTempValue = 0;
		char* Tempoperators = new char[nNoOfNumbers - 2]{'\0'};
		int nValue = 0;
		int* TempNumbers = new int[nNoOfNumbers - 1]();
		bool bhigherPriority = false;

		for (i = 0; i < (nNoOfNumbers - 1); i++)
		{
			const char cTemp = operators[i];
			TempNumbers[i] = nNumbers[i];
			if (i != (nNoOfNumbers - 2))
				Tempoperators[i] = operators[i];
			if ((cTemp == '*') || (cTemp == '/'))
			{
				nTempValue = i;
				bhigherPriority = true;
				break;
			}
		}
		if (bhigherPriority)
		{
			nValue = evaluateString(nNumbers[i], nNumbers[i + 1], &operators[i]);
			TempNumbers[i] = nValue;
			for (i = nTempValue + 1; i < (nNoOfNumbers - 1); i++)
				TempNumbers[i] = nNumbers[i + 1];

			for (i = nTempValue; i < (nNoOfNumbers - 2); i++)
				Tempoperators[i] = operators[i + 1];

			evaluateExpression(Tempoperators, TempNumbers, nNoOfNumbers - 1, nResultValue);
		}
		else
		{
			int nTemp = 0;
			nTemp = nNumbers[0];
			for (int i = 0; i < (nNoOfNumbers - 1); i++)
			{
				nTemp = evaluateString(nTemp, nNumbers[i + 1], &operators[i]);
			}
			*nResultValue = nTemp;
		}

	}
	else
	{
		*nResultValue = evaluateString(nNumbers[0], nNumbers[1], &operators[0]);
	}


	return 0;
}

int permutation(char* characterTobeSwaped, int nNoOfCharacters, char* characterTobeRetained,int nNoOfRetainedChar, char*** originalArray)
{
	char tempChar[4] = "";
	char cCharacterTobeSwapped[4] = "";
	int i = 0;
	for (i = 0; i < nNoOfRetainedChar; i++)
		tempChar[i] = characterTobeRetained[i];

	if (nNoOfCharacters > 2)
	{
		for (int j = 0; j < nNoOfCharacters; j++)
		{
			tempChar[i] = characterTobeSwaped[0];

			for (int l = 1; l < nNoOfCharacters; l++)
				cCharacterTobeSwapped[l - 1] = characterTobeSwaped[l];

			permutation(cCharacterTobeSwapped, nNoOfCharacters - 1, tempChar, nNoOfRetainedChar + 1, originalArray);

			swap(characterTobeSwaped, nNoOfCharacters);

		}
	}
	else
	{
		int k = 0;

		for (int jj = 0; jj < 2; jj++)
		{
			for (k = 0; k < nNoOfRetainedChar; k++)
				originalArray[0][nIndex][k] = characterTobeRetained[k];

			if (jj == 0)
			{
				originalArray[0][nIndex][k] = characterTobeSwaped[0];
				k++;
				originalArray[0][nIndex][k] = characterTobeSwaped[1];
			}
			else
			{
				originalArray[0][nIndex][k] = characterTobeSwaped[1];
				k++;
				originalArray[0][nIndex][k] = characterTobeSwaped[0];
			}

			nIndex++;
		}
	}
	return 0;

}

//repetation of the operators not allowed
int mixedNumbers(int* nNumbers,int nNoOfNumbers, int nResultValue)
{
	int nNumberOfOperators = nNoOfNumbers - 1, nNoOfWays = 0, nPermutaion = 0, temp = 0, j = 0, nNumberOfavailableoperators = 4, nStatus = -1;
	char operators[4] = { '+','-','/','*' };
	bool bIncreaseAllThePivot = false, bIncreaseSecondaryPivots = false;

	if (nNumberOfOperators < 1)
		return 1;


	//finding the number of combinations.
	// find the number of operators required.(nCr = no of combination)
	int nNoOfCombinations = ((factorial(4)) / ((factorial(nNumberOfOperators)) * (factorial(4 - nNumberOfOperators))));

	nPermutaion = factorial(nNumberOfOperators);
	nNoOfWays = nPermutaion * nNoOfCombinations;

	char** CombinationArray = new char* [nNoOfCombinations];

	int* pivot = new int[nNumberOfOperators]();

	for (j = 0; j < nNumberOfOperators; j++)
		pivot[j] = j;

	for (int i = 0; i < nNoOfCombinations; i++)
	{
		char* cCombination = new char[nNumberOfOperators] {'\0'};

		CombinationArray[i] = cCombination;

		for (int k = 0; k < nNumberOfOperators; k++)
			cCombination[k] = operators[pivot[k]];

		//change the last pivot value
		temp = pivot[nNumberOfOperators - 1];

		bIncreaseAllThePivot = false;
		bIncreaseSecondaryPivots = false;

		//two type of pivots - main pivot and the remaining are the secondary pivot
		//once the secondary pivot value cannot be incremented, increase all the pivot value


		if (nNumberOfOperators == 1)
			bIncreaseAllThePivot = true;
		else if (temp == (nNumberOfavailableoperators - 1))
		{
			temp = pivot[nNumberOfOperators - 2];

			if (temp == (nNumberOfavailableoperators - 2))
				bIncreaseAllThePivot = true;
			else if (temp == (nNumberOfavailableoperators - 3))
				bIncreaseSecondaryPivots = true;
		}
		else
			pivot[nNumberOfOperators - 1]++;

		if (bIncreaseSecondaryPivots)
		{
			temp = pivot[1];
			for (int jj = 1; jj < nNumberOfOperators; jj++)
			{
				temp++;
				pivot[jj] = temp;
			}
		}
		else if (bIncreaseAllThePivot)
		{
			temp = pivot[0];
			for (int jj = 0; jj < nNumberOfOperators; jj++)
			{
				temp++;
				pivot[jj] = temp;
			}
		}
	}
	char** TotalCombinationArray = new char* [nNoOfWays];
	for (int i = 0; i < nNoOfWays; i++)
	{
		char* cCombination = new char[nNumberOfOperators] {'\0'};

		TotalCombinationArray[i] = cCombination;
	}

	// permutation of the operators

	for (int i = 0; i < nNoOfCombinations; i++)
		permutation(CombinationArray[i], nNumberOfOperators, NULL, 0, &TotalCombinationArray);

	//Evaluate expression for the given operator combinations

	for (int i = 0; i < nNoOfWays; i++)
	{
		int nTempResultValue = 0;
		evaluateExpression(TotalCombinationArray[i], nNumbers, nNoOfNumbers, &nTempResultValue);

		if (nTempResultValue == nResultValue)
		{

			if (nStatus == -1)
				cout << "\n" << "the combination obtained is \n";
			else
				cout << "\n";

			nStatus = 0;
			cout << nNumbers[0];
			for (int k = 0; k < nNumberOfOperators; k++)
				cout << "  " << TotalCombinationArray[i][k]<<"  "<< nNumbers[k+1]<<"  ";

			cout << "=  " << nResultValue;
		}
	}

	return nStatus;
}

int main()
{
	int nNoOfNumbers = 0, nResultValue = 0, nStatus = 0;

	cout << "enter the no of numbers";

	cin >> nNoOfNumbers;

	if (nNoOfNumbers > 5)
	{
		cout << "eneter the no of numbers between 2 and 5";
		return -1;
	}

	cout << "\n enter the number in exact order";


	int* nNumbers = new int[nNoOfNumbers]();

	for (int i = 0; i < nNoOfNumbers; i++)
	{
		cout << "\n";
		cin >> nNumbers[i];
	}

	cout << "\n enter the value to be obtained";

	cin >> nResultValue;

	nStatus = mixedNumbers(nNumbers, nNoOfNumbers, nResultValue);

	if (nStatus != 0)
		cout << "invalid input";


	return 0;
}