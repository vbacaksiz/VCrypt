#include "Crypt.h"

int** allOutputText;

int VC[KEYSCHEDULEAREASIZE][BITSIZE] = {
	{1,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,1,0},
	{0,0,1,0,0,1,0,0},
	{0,0,0,1,1,0,0,0}
};

int SBox[BYTESIZE][BYTESIZE] = {
	{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
	{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
	{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
	{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
	{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
	{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
	{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
	{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
	{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
	{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
	{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
	{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
	{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
	{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
	{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
	{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

int inverseSBox[BYTESIZE][BYTESIZE] = {
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
	{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
	{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
	{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
	{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
	{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
	{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
	{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
	{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
	{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
	{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
	{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
	{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
	{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
	{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
	{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

int initializationVector[BYTESIZE][BITSIZE] = {
	{1,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,0,1},
	{0,1,0,0,0,0,1,0},
	{0,0,1,0,0,0,1,0},
	{0,0,1,0,0,1,0,0},
	{0,0,0,1,0,1,0,0},
	{0,0,0,1,1,0,0,0},
	{1,0,0,1,1,0,0,0},
	{1,0,0,1,1,0,0,1},
	{0,1,0,1,1,0,0,1},
	{0,1,0,1,1,0,1,0},
	{0,0,1,1,1,0,1,0},
	{0,0,1,1,1,1,0,0},
	{1,0,1,1,1,1,0,0},
	{1,0,1,1,1,1,0,1},
};

using namespace std;

//Sample Text
//Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry.

int** GetOneByteToBinary(int** outputArray, char letter, int byteNumber)
{
	int ASCIIValue = (int)letter;
	outputArray[byteNumber] = new int[BITSIZE];
	for (int j = 7; j >= 0; j--)
	{
		if (ASCIIValue >= pow(2, j))
		{
			outputArray[byteNumber][j] = 1;
			ASCIIValue -= pow(2, j);
		}
		else
		{
			outputArray[byteNumber][j] = 0;
		}
	}
	return outputArray;
}

int** GetOneByteToBinary(int** outputArray, int decimal, int byteNumber)
{
	int decimalValue = decimal;
	outputArray[byteNumber] = new int[BITSIZE];
	for (int j = 7; j >= 0; j--)
	{
		if (decimalValue >= pow(2, j))
		{
			outputArray[byteNumber][j] = 1;
			decimalValue -= pow(2, j);
		}
		else
		{
			outputArray[byteNumber][j] = 0;
		}
	}
	return outputArray;
}

int** GetByteToBinary(int** outputArray, string text, int lastPoint)
{
	outputArray = new int*[lastPoint];
	for (int i = 0; i < lastPoint; i++)
	{
		GetOneByteToBinary(outputArray, text[i], i);
	}
	return outputArray;
}

int** GetByteToBinary(int** outputArray, int* decimalArray, int lastPoint)
{
	outputArray = new int*[lastPoint];
	for (int i = 0; i < lastPoint; i++)
	{
		GetOneByteToBinary(outputArray, decimalArray[i], i);
	}
	return outputArray;
}

void PrintByteByByte(int** text, int byteNumber)
{
	for (int j = byteNumber - 1; j >= 0; j--)
	{
		for (int i = BITSIZE - 1; i >= 0; i--)
		{
			cout << text[j][i];
		}
		cout << endl;
	}
}

void PrintAll(int** text, int byteNumber)
{
	for (int j = 0; j < byteNumber; j++)
	{
		for (int i = BITSIZE - 1; i >= 0; i--)
		{
			cout << text[j][i];
		}
		cout << "  ";
	}
	cout << endl;
}

int DivideText(int length)
{
	int remainderLength = length - BYTESIZE;
	return remainderLength;
}

int** SecondDimensionForNewArray(int** text, int byteNumber, int length)
{
	text[byteNumber] = new int[length];
	for (int j = 7; j >= 0; j--)
	{
		text[byteNumber][j] = 0;
	}
	return text;
}

int** CreateNewArray(int** newText, int length)
{
	newText = new int*[length];
	for (int i = 0; i < length; i++)
	{
		SecondDimensionForNewArray(newText, i, BITSIZE);
	}
	return newText;
}

int** FillArray(int** text, int startPoint, int endPoint)
{
	for (int i = startPoint; i < endPoint; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			text[i][j] = 0;
		}
	}
	return text;
}

int** CopyArray(int** getObjArray, int** array)
{
	for (int i = 0; i < BYTESIZE; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			getObjArray[i][j] = array[i][j];
		}
	}
	return getObjArray;
}

int** CopyArray(int** getObjArray, int array[BYTESIZE][BITSIZE])
{
	for (int i = 0; i < BYTESIZE; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			getObjArray[i][j] = array[i][j];
		}
	}
	return getObjArray;
}

int** CopyArray(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex)
{
	for (int i = 0; i < BYTESIZE; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			getObjArray[i + firstArrayIndex][j] = array[i + secondArrayIndex][j];
		}
	}
	return getObjArray;
}

int** CopyArray(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex, int firstDimensionLoopSize)
{
	for (int i = 0; i < firstDimensionLoopSize; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			getObjArray[i + firstArrayIndex][j] = array[i + secondArrayIndex][j];
		}
	}
	return getObjArray;
}

int** CopyBits(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex)
{
	for (int i = BITSIZE - 1; i >= 0; i--)
	{
		getObjArray[firstArrayIndex][i] = array[secondArrayIndex][i];
	}
	return getObjArray;
}

int** XOR(int** outputArray, int** inputArray, int outputIndex, int firstIndex, int secondIndex)
{
	for (int i = 0; i < BITSIZE; i++)
	{
		if (inputArray[firstIndex][i] == inputArray[secondIndex][i])
			outputArray[outputIndex][i] = 0;
		else
			outputArray[outputIndex][i] = 1;
	}
	return outputArray;
}

int** XOR(int** outputArray, int** inputArray, int outputIndex, int firstIndex, int secondIndex, int loopSize)
{
	for (int j = 0; j < loopSize; j++)
	{
		for (int i = 0; i < BITSIZE; i++)
		{
			if (outputArray[firstIndex + j][i] == inputArray[secondIndex + j][i])
				outputArray[outputIndex + j][i] = 0;
			else
				outputArray[outputIndex + j][i] = 1;
		}
	}
	return outputArray;
}

int** DecimalToBinary(int** outputArray, int decimal, int index)
{
	for (int j = 7; j >= 0; j--)
	{
		if (decimal >= pow(2, j))
		{
			outputArray[index][j] = 1;
			decimal -= pow(2, j);
		}
		else
		{
			outputArray[index][j] = 0;
		}
	}
	return outputArray;
}

int CalculateDecimal(int** text, int i, int startPoint, int loopSize = 4)
{
	int decimal = 0;
	for (int k = 0; k < loopSize; k++)
	{
		if (text[i][startPoint + k] == 1)
			decimal += pow(2, k);
	}
	return decimal;
}

int CalculateDecimal(int** text, int i)
{
	int decimal = 0;
	for (int k = 0; k < BITSIZE; k++)
	{
		if (text[i][k] == 1)
			decimal += pow(2, k);
	}
	return decimal;
}

char* GetOutputChar(int** text, int length)
{
	unsigned char letter;
	char* a = (char*)malloc(length);
	string encryptedString;
	for (int i = 0; i < length; i++)
	{
		int decimal = CalculateDecimal(text, i);
		letter = static_cast<unsigned char>(decimal);
		a[i] = letter;
		encryptedString += letter;
	}
	return a;
}

//Use SBox for encryption
int** SBoxTransactionsForEncryption(int** outputArray)
{
	int firstFourDecimal = 0;
	int lastFourDecimal = 0;
	int SBoxValue = 0;
	for (int i = 0; i < BYTESIZE; i++)
	{
		firstFourDecimal = CalculateDecimal(outputArray, i, 0);
		lastFourDecimal = CalculateDecimal(outputArray, i, 4);
		SBoxValue = SBox[lastFourDecimal][firstFourDecimal];
		outputArray = DecimalToBinary(outputArray, SBoxValue, i);
	}
	return outputArray;
}

//Encryption - Start

int** DivideProcessForEncryption(int** inputText, int** outputText, int length)
{
	if (length <= 0)
	{
		return outputText;
	}
	else
	{
		int totalProcess = 0;
		int sideCounter = 0;
		bool side = true;
		while (totalProcess != BYTESIZE)
		{
			if (sideCounter == length + 1)
			{
				side = !side;
				sideCounter = 0;
			}
			if (side)
			{
				if (totalProcess % 2 == 0)
				{
					outputText = XOR(outputText, inputText, totalProcess, totalProcess, totalProcess + length + 2);
				}
				else
				{
					outputText = CopyBits(outputText, inputText, totalProcess, totalProcess + length);
				}
			}
			else
			{
				if (totalProcess % 2 == 0)
				{
					outputText = CopyBits(outputText, inputText, totalProcess, totalProcess - length);
				}
				else
				{
					outputText = CopyBits(outputText, inputText, totalProcess, totalProcess);
				}
			}
			sideCounter++;
			totalProcess++;
		}
		inputText = CopyArray(inputText, outputText);
		DivideProcessForEncryption(inputText, outputText, ((length + 1) / 2) - 1);
	}
	return outputText;
}

int** DivideForEncryption(int** forProcessText, int** processText)
{
	int** copyText = CreateNewArray(copyText, BYTESIZE);
	copyText = CopyArray(copyText, processText);
	forProcessText = DivideProcessForEncryption(copyText, forProcessText, (BYTESIZE / 2) - 1);
	free(copyText);
	return forProcessText;
}

int** MergeProcessForEncryption(int** inputText, int** outputText, int length)
{
	if (length >= 4)
	{
		return outputText;
	}
	else
	{
		int totalProcess = 0;
		int sideCounter = 0;
		bool side = true;
		while (totalProcess != BYTESIZE)
		{
			if (sideCounter == length)
			{
				side = !side;
				sideCounter = 0;
			}
			if (side)
			{
				if (totalProcess % 2 == 0)
				{
					outputText = CopyBits(outputText, inputText, ((BYTESIZE - 1) - totalProcess), totalProcess);
				}
				else
				{
					outputText = XOR(outputText, inputText, totalProcess + 1, totalProcess, ((BYTESIZE - 1) - totalProcess));
				}
			}
			else
			{
				if (totalProcess % 2 == 0)
				{
					outputText = CopyBits(outputText, inputText, (totalProcess - 1), totalProcess);
				}
				else
				{
					outputText = CopyBits(outputText, inputText, (totalProcess - (pow(2, length) - 1)), totalProcess);
				}
			}
			sideCounter++;
			totalProcess++;
		}
		inputText = CopyArray(inputText, outputText);
		MergeProcessForEncryption(inputText, outputText, (length * 2));
	}
	return outputText;
}

int** MergeForEncryption(int** forProcessText, int** processText)
{
	int** copyText = CreateNewArray(copyText, BYTESIZE);
	copyText = CopyArray(copyText, forProcessText);
	forProcessText = MergeProcessForEncryption(copyText, forProcessText, 1);
	free(copyText);
	return forProcessText;
}

int** EncryptionProcess(int** processText)
{
	int** processedText;
	processedText = CreateNewArray(processedText, BYTESIZE);
	processedText = DivideForEncryption(processedText, processText);
	processedText = MergeForEncryption(processedText, processText);
	return processedText;
}

int** Encryption(string input, string key)
{
	int textLength = input.length();
	int** processText = CreateNewArray(processText, BYTESIZE);
	int** copyTextForProcess = CreateNewArray(copyTextForProcess, BYTESIZE);
	int** keyText = CreateNewArray(keyText, BYTESIZE);
	int remainderLength = textLength;
	int lastPoint = 0;
	while (remainderLength >= BYTESIZE)
	{
		remainderLength = DivideText(remainderLength);
		lastPoint += BYTESIZE;
	}
	if (remainderLength > 0)
	{
		lastPoint += BYTESIZE;
	}
	allOutputText = GetByteToBinary(allOutputText, input, textLength);
	int** tmpAllOutputText = CreateNewArray(tmpAllOutputText, BYTESIZE);
	int** encryptedText = CreateNewArray(encryptedText, BYTESIZE);
	int** CBCXORText = CreateNewArray(CBCXORText, BYTESIZE);
	CBCXORText = CopyArray(CBCXORText, initializationVector);
	int** encryptResultText = CreateNewArray(encryptResultText, lastPoint);
	remainderLength = textLength;
	lastPoint = 0;
	while (remainderLength >= BYTESIZE)
	{
		remainderLength = DivideText(remainderLength);
		tmpAllOutputText = CopyArray(tmpAllOutputText, allOutputText, 0, lastPoint);
		tmpAllOutputText = XOR(tmpAllOutputText, CBCXORText, 0, 0, 0, BYTESIZE);
		keyText = GetByteToBinary(keyText, key, BYTESIZE);
		for (int i = 0; i < MAXROUNDNUMBER; i++)
		{
			copyTextForProcess = CopyArray(copyTextForProcess, tmpAllOutputText);
			copyTextForProcess = SBoxTransactionsForEncryption(copyTextForProcess);
			processText = EncryptionProcess(copyTextForProcess);
			encryptedText = CopyArray(encryptedText, processText, 0, 0);
			keyText = GetKeyForEncryption(keyText, key, i);
			encryptedText = XOR(encryptedText, keyText, 0, 0, 0, BYTESIZE);
			tmpAllOutputText = CopyArray(tmpAllOutputText, encryptedText);
		}
		encryptResultText = CopyArray(encryptResultText, encryptedText, lastPoint, 0);
		CBCXORText = CopyArray(CBCXORText, encryptedText);
		lastPoint += BYTESIZE;
	}
	if (remainderLength > 0)
	{
		tmpAllOutputText = CopyArray(tmpAllOutputText, allOutputText, 0, lastPoint, remainderLength);
		tmpAllOutputText = FillArray(tmpAllOutputText, remainderLength, BYTESIZE);
		tmpAllOutputText = XOR(tmpAllOutputText, CBCXORText, 0, 0, 0, BYTESIZE);
		keyText = GetByteToBinary(keyText, key, BYTESIZE);
		for (int i = 0; i < MAXROUNDNUMBER; i++)
		{
			copyTextForProcess = CopyArray(copyTextForProcess, tmpAllOutputText);
			copyTextForProcess = SBoxTransactionsForEncryption(copyTextForProcess);
			processText = EncryptionProcess(copyTextForProcess);
			encryptedText = CopyArray(encryptedText, processText, 0, 0);
			keyText = GetKeyForEncryption(keyText, key, i);
			encryptedText = XOR(encryptedText, keyText, 0, 0, 0, BYTESIZE);
			tmpAllOutputText = CopyArray(tmpAllOutputText, encryptedText);
		}
		encryptResultText = CopyArray(encryptResultText, encryptedText, lastPoint, 0);
	}
	free(CBCXORText);
	free(copyTextForProcess);
	free(keyText);
	free(processText);
	free(tmpAllOutputText);
	free(allOutputText);
	return encryptResultText;
}

int** GetInputTextForEncryption(string input, string key)
{
	int** encryptedText = Encryption(input, key);
	return encryptedText;
}

//Encryption -- Finish

//Key Schedule -- Start

int** SBoxTransactionsForKey(int** outputArray, int loopSize)
{
	int firstFourDecimal = 0;
	int lastFourDecimal = 0;
	int SBoxValue = 0;
	for (int i = 0; i < loopSize; i++)
	{
		firstFourDecimal = CalculateDecimal(outputArray, i, 0);
		lastFourDecimal = CalculateDecimal(outputArray, i, 4);
		SBoxValue = SBox[lastFourDecimal][firstFourDecimal];
		outputArray = DecimalToBinary(outputArray, SBoxValue, i);
	}
	return outputArray;
}

int** VFunction(int** inputText, int** outputText, int numOfRound)
{
	int shift = numOfRound % KEYSCHEDULEAREASIZE;
	int** lastFourByte = CreateNewArray(lastFourByte, KEYSCHEDULEAREASIZE);
	lastFourByte = CopyArray(lastFourByte, inputText, 0, 0 + (BYTESIZE - KEYSCHEDULEAREASIZE), KEYSCHEDULEAREASIZE);
	int** tmpLastFourByte = CreateNewArray(tmpLastFourByte, KEYSCHEDULEAREASIZE);
	tmpLastFourByte = CopyArray(tmpLastFourByte, lastFourByte, 0, 0, KEYSCHEDULEAREASIZE);
	int i = 0;
	int positionThenShift = KEYSCHEDULEAREASIZE - shift;
	while (i != KEYSCHEDULEAREASIZE)
	{
		positionThenShift %= KEYSCHEDULEAREASIZE;
		lastFourByte = CopyBits(lastFourByte, tmpLastFourByte, positionThenShift, i);
		i++;
		positionThenShift++;
	}
	free(tmpLastFourByte);
	lastFourByte = SBoxTransactionsForKey(lastFourByte, KEYSCHEDULEAREASIZE);
	int** tmpVC = CreateNewArray(tmpVC, KEYSCHEDULEAREASIZE);
	for (int j = 0; j < KEYSCHEDULEAREASIZE; j++)
	{
		for (int k = 0; k < BITSIZE; k++)
		{
			tmpVC[j][k] = VC[j][k];
		}
	}
	lastFourByte = XOR(lastFourByte, tmpVC, 0, 0, shift, 1);
	outputText = CopyArray(outputText, inputText, 0, 0, BYTESIZE - KEYSCHEDULEAREASIZE);
	outputText = CopyArray(outputText, lastFourByte, BYTESIZE - KEYSCHEDULEAREASIZE, 0, KEYSCHEDULEAREASIZE);
	return outputText;
}

int** AllXORs(int** inputText)
{
	inputText = XOR(inputText, inputText, 0, 0, BYTESIZE - KEYSCHEDULEAREASIZE, KEYSCHEDULEAREASIZE);
	for (int i = 1; i < KEYSCHEDULEAREASIZE; i++)
	{
		inputText = XOR(inputText, inputText, i*KEYSCHEDULEAREASIZE, (i - 1)*KEYSCHEDULEAREASIZE, i*KEYSCHEDULEAREASIZE, KEYSCHEDULEAREASIZE);
	}
	return inputText;
}

int** KeySchedule(int** inputText, int numOfRound)
{
	int** outputKey = CreateNewArray(outputKey, BYTESIZE);
	outputKey = VFunction(inputText, outputKey, numOfRound);
	outputKey = AllXORs(outputKey);
	return outputKey;
}

int** GetKeyForEncryption(int** keyText, string key, int numOfRound)
{
	keyText = KeySchedule(keyText, numOfRound);
	return keyText;
}

//Key Schedule -- Finish

//Decryption - Start

//Use inverse SBox for decryption
int** SBoxTransactionsForDecryption(int** outputArray)
{
	int firstFourDecimal = 0;
	int lastFourDecimal = 0;
	int SBoxValue = 0;
	for (int i = 0; i < BYTESIZE; i++)
	{
		firstFourDecimal = CalculateDecimal(outputArray, i, 0);
		lastFourDecimal = CalculateDecimal(outputArray, i, 4);
		SBoxValue = inverseSBox[lastFourDecimal][firstFourDecimal];
		outputArray = DecimalToBinary(outputArray, SBoxValue, i);
	}
	return outputArray;
}

int** DivideProcessForDecryption(int** inputText, int** outputText, int length)
{
	if (length <= 1)
	{
		return outputText;
	}
	else
	{
		int totalProcess = 0;
		int counter = 0;
		while (totalProcess != BYTESIZE)
		{
			if (totalProcess % length == 0 && (length - 1) != 0)
			{
				counter++;
				outputText = CopyBits(outputText, inputText, (counter * length) - 1, totalProcess);
			}
			else if (totalProcess % length == 1 && (length - 1) != 1)
			{
				outputText = CopyBits(outputText, inputText, (counter * length) - 2, totalProcess);
			}
			else if (totalProcess % length == 2 && (length - 1) != 2)
			{
				outputText = XOR(outputText, inputText, (counter * length) - 3, totalProcess, ((BYTESIZE - 1) - totalProcess));
			}
			else if (totalProcess % length == (length - 1))
			{
				outputText = CopyBits(outputText, inputText, (BYTESIZE - 1) - ((counter* length) - 1), totalProcess);
			}
			totalProcess++;
		}
		inputText = CopyArray(inputText, outputText);
		DivideProcessForDecryption(inputText, outputText, length / 2);
	}
	return outputText;
}

int** DivideForDecryption(int** forProcessText, int** processText)
{
	int** copyText = CreateNewArray(copyText, BYTESIZE);
	copyText = CopyArray(copyText, processText);
	forProcessText = DivideProcessForDecryption(copyText, forProcessText, (BYTESIZE / 4));
	free(copyText);
	return forProcessText;
}

int** MergeProcessForDecryption(int** inputText, int** outputText, int length)
{
	if (length >= 15)
	{
		return outputText;
	}
	else
	{
		int totalProcess = 0;
		int sideCounter = 0;
		bool side = true;
		while (totalProcess != BYTESIZE)
		{
			if (sideCounter == length + 1)
			{
				side = !side;
				sideCounter = 0;
			}
			if (side)
			{
				if (totalProcess % 2 == 0)
				{
					outputText = XOR(outputText, inputText, totalProcess, totalProcess, totalProcess + length + 2);
				}
				else
				{
					outputText = CopyBits(outputText, inputText, totalProcess + length, totalProcess);
				}
			}
			else
			{
				if (totalProcess % 2 == 0)
				{
					outputText = CopyBits(outputText, inputText, totalProcess - length, totalProcess);
				}
				else
				{
					outputText = CopyBits(outputText, inputText, totalProcess, totalProcess);
				}
			}
			sideCounter++;
			totalProcess++;
		}
		inputText = CopyArray(inputText, outputText);
		MergeProcessForDecryption(inputText, outputText, ((length + 1) * 2) - 1);
	}
	return outputText;
}

int** MergeForDecryption(int** forProcessText, int** processText)
{
	int** copyText = CreateNewArray(copyText, BYTESIZE);
	copyText = CopyArray(copyText, forProcessText);
	forProcessText = MergeProcessForDecryption(copyText, forProcessText, 1);
	free(copyText);
	return forProcessText;
}

int** DecryptionProcess(int** processText)
{
	int** processedText;
	processedText = CreateNewArray(processedText, BYTESIZE);
	processedText = DivideForDecryption(processedText, processText);
	processedText = MergeForDecryption(processedText, processText);
	return processedText;
}

string Decryption(int* decimalArray, int arrayLength, string key)
{
	int textLength = arrayLength;
	int** processText = CreateNewArray(processText, BYTESIZE);
	int** copyTextForProcess = CreateNewArray(copyTextForProcess, BYTESIZE);
	int** keyText = CreateNewArray(keyText, BYTESIZE);
	int remainderLength = textLength;
	int lastPoint = arrayLength;
	allOutputText = GetByteToBinary(allOutputText, decimalArray, lastPoint);
	int** tmpAllOutputText = CreateNewArray(tmpAllOutputText, BYTESIZE);
	int** decryptedText = CreateNewArray(decryptedText, BYTESIZE);
	int** CBCXORText = CreateNewArray(CBCXORText, BYTESIZE);
	int** decryptResultText = CreateNewArray(decryptResultText, lastPoint);
	CBCXORText = CopyArray(CBCXORText, initializationVector);
	remainderLength = textLength;
	lastPoint = 0;
	while (remainderLength >= BYTESIZE)
	{
		remainderLength = DivideText(remainderLength);
		tmpAllOutputText = CopyArray(tmpAllOutputText, allOutputText, 0, lastPoint);
		for (int i = 0; i < MAXROUNDNUMBER; i++)
		{
			copyTextForProcess = CopyArray(copyTextForProcess, tmpAllOutputText);
			keyText = GetByteToBinary(keyText, key, BYTESIZE);
			keyText = GetKeyForDecryption(keyText, key, MAXROUNDNUMBER - i);
			copyTextForProcess = XOR(copyTextForProcess, keyText, 0, 0, 0, BYTESIZE);
			processText = DecryptionProcess(copyTextForProcess);
			decryptedText = CopyArray(decryptedText, processText, 0, 0);
			decryptedText = SBoxTransactionsForDecryption(decryptedText);
			tmpAllOutputText = CopyArray(tmpAllOutputText, decryptedText);
		}
		decryptedText = XOR(decryptedText, CBCXORText, 0, 0, 0, BYTESIZE);
		decryptResultText = CopyArray(decryptResultText, decryptedText, lastPoint, 0);
		CBCXORText = CopyArray(CBCXORText, allOutputText, 0, lastPoint);
		lastPoint += BYTESIZE;
	}
	free(CBCXORText);
	free(copyTextForProcess);
	free(processText);
	free(keyText);
	string output = GetOutputChar(decryptResultText, lastPoint);
	free(decryptedText);
	free(allOutputText);
	return output;
}

string GetInputTextForDecryption(string decimalInput, string key)
{
	int* decimalArray;
	int arrayLength = 0;
	decimalArray = (int*)malloc(decimalInput.length() * 16);
	int decimalStep = 0;
	for (int i = 0; i <= decimalInput.length(); i++)
	{
		if (decimalInput[i] == ' ' || i == decimalInput.length())
		{
			int sum = 0;
			for (int j = 0; j < decimalStep; j++)
			{
				char charValue = (char)decimalInput[(i - 1) - j];
				int decimalValue = charValue - '0';
				sum += decimalValue * pow(10, j);
			}
			decimalArray[arrayLength] = sum;
			arrayLength++;
			decimalStep = 0;
		}
		else
			decimalStep++;
	}
	string firstDecryptedText = Decryption(decimalArray, arrayLength, key);
	string lastDecryptedText = firstDecryptedText.substr(0, arrayLength);
	return lastDecryptedText;
}

//Decryption -- Finish

//Key Schedule For Decryption
int** GetKeyForDecryption(int** keyText, string key, int numOfRound)
{
	for (int i = 0; i < numOfRound; i++)
	{
		keyText = KeySchedule(keyText, i);
	}
	return keyText;
}