// OpenMPTest.cpp: определяет точку входа для консольного приложения.
//
#pragma warning(disable:4996)
#include <omp.h>
#include "stdafx.h"
#include <iostream>
#include <ppl.h>
#include <chrono>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include "OpenMPTest.h"
using namespace std;
int main0()
{

	int number = 10000000000;
	vector<int> x(number), y(number + 4);
	//int x[244], y[246];
	for (int i = 0; i < number; i++)
	{
		y[i] = i;
	}
	auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for
	for (int i = 1; i < number; ++i)
	{
		x[i] = (y[i - 1] + y[i + 1]) / 2;
		//printf("%d\n", x[i]);
	}
	cout << chrono::duration_cast<chrono::milliseconds>
		(chrono::high_resolution_clock::now() - start).count() << "ms" << endl;
	//cout << result. << endl;
	return 0;
}
//есть файл, его надо считать побайтово и сдвинуть каждый байт на 1 константу.

char op_shift_left(char i) { return --i; }
char op_shift_right(char i) { return ++i; }

void createLargeBook()
{
	string inFilePath = "D:\\Downloads\\book1.txt", outFileName = "bookForTest.txt";
	ifstream inFile(inFilePath);
	ofstream outFile(outFileName, std::ofstream::trunc);
	int block_size = 1024 * 1024;
	vector<char> t(block_size + 4);
	int times = 100;
	while (true)
	{
		vector<char> t(block_size + 4);
		inFile.read(&t[0], block_size);
		for (int i = 0; i < times; i++)
		{
			outFile << &t[0];
		}
		if (inFile.eof()) break;
	}
}//написать параллельно и замерить время в сравнении с последовательной.
bool TestFile(string basicFile, string resultFile)
{
	return false;
}

vector<unsigned char>base64Transform(vector<unsigned char> &inBlock, string &encodingString)//TODO: change char for guaranteed 8-bit type
{
	vector<char> indexes(4);
	vector<unsigned char> outBlock(4);
	if (inBlock.size() <= 0 || inBlock.size() > 3) cerr << "input error";//TODO: Make cpp exception
	else //could make a switch w/o copy-paste, but it will make the code much unreadable. Also< is there conditional switch in c++?
	{
		if (inBlock.size() == 3)
		{
			indexes[0] = inBlock[0] >> 2;
			indexes[1] = ((inBlock[0] & 0b00000011) << 4) + ((inBlock[1] & 0b11110000) >> 4);
			indexes[2] = ((inBlock[1] & 0b00001111) << 2) + ((inBlock[2] & 0b11000000) >> 6);
			indexes[3] = inBlock[2] & 0b00111111;
			for (size_t i = 0; i < 4; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
		}
		else if (inBlock.size() == 2)
		{
			indexes[0] = inBlock[0] >> 2;
			indexes[1] = ((inBlock[0] & 0b00000011) << 4) + ((inBlock[1] & 0b11110000) >> 4);
			indexes[2] = ((inBlock[1] & 0b00001111) << 2);// + ((inBlock[2] & 0b11000000) >> 6);
			//indexes[3] = inBlock[2] & 0b00111111;
			for (size_t i = 0; i < 3; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
			outBlock[3] = '=';
		}
		else //one input char 
		{
			indexes[0] = inBlock[0] >> 2;
			indexes[1] = ((inBlock[0] & 0b00000011) << 4);//+ ((inBlock[1] & 0b11110000) >> 4);
			//indexes[2] = ((inBlock[1] & 0b00001111) << 2) + ((inBlock[2] & 0b11000000) >> 6);
			//indexes[3] = inBlock[2] & 0b00111111;
			for (size_t i = 0; i < 2; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
			outBlock[2] = '=';
			outBlock[3] = '=';
		}
	}
	return outBlock;
}

void base64Transform(vector<unsigned char> &inVector, vector<unsigned char> &outVector, unsigned int inVecIndex,unsigned int outVecIndex, string &encodingString)//TODO: make it const type
{
	vector<char> indexes(4);
	vector<unsigned char> outBlock(4);
	if (inVecIndex>inVector.size() || inVecIndex<0) cerr << "input error";//TODO: Make cpp exception
	else //could make a switch w/o copy-paste, but it will make the code much unreadable. Also< is there conditional switch in c++?
	{
		if (inVector.size() - 3)
		{
			indexes[0] = inVector[inVecIndex] >> 2;
			indexes[1] = ((inVector[inVecIndex] & 0b00000011) << 4) + ((inVector[inVecIndex+1] & 0b11110000) >> 4);
			indexes[2] = ((inVector[inVecIndex+1] & 0b00001111) << 2) + ((inVector[inVecIndex+2] & 0b11000000) >> 6);
			indexes[3] = inVector[inVecIndex+2] & 0b00111111;
			for (size_t i = 0; i < 4; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
		}
		else if (inVector.size() == 2)
		{
			indexes[0] = inVector[inVecIndex] >> 2;
			indexes[1] = ((inVector[inVecIndex] & 0b00000011) << 4) + ((inVector[inVecIndex+1] & 0b11110000) >> 4);
			indexes[2] = ((inVector[inVecIndex+1] & 0b00001111) << 2);
			for (size_t i = 0; i < 3; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
			outBlock[3] = '=';
		}
		else //one input char 
		{
			indexes[0] = inVector[inVecIndex] >> 2;
			indexes[1] = ((inVector[inVecIndex] & 0b00000011) << 4);
			for (size_t i = 0; i < 2; i++)
			{
				outBlock[i] = encodingString[indexes[i]];
			}
			outBlock[2] = '=';
			outBlock[3] = '=';
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		outVector[i + outVecIndex] = outBlock[i];//no optimisation 4 today.

	}
}

const unsigned int calculateResultLength(const int inputLength)//We think that we process strings on in and out
{
	return ((inputLength / 3) + (inputLength % 3 != 0)) * 4;
}

void b64test1()
{
	string testInString = "Man", testOutString = "TWFu", b64EncodingString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned int resultLength = 4;
	vector<unsigned char> testIn(testInString.begin(), testInString.end()), testOut(testOutString.begin(), testOutString.end()), transformResult(4);
	transformResult = base64Transform(testIn, b64EncodingString);
	if (testOut == transformResult)
		cout << "Well done, test 1 completed" << endl;
	else
	{
		for (auto i : transformResult)
			cout << i;
		cout << endl;
	}
}

void b64test2()
{
	string testInString = "Man is distinguished, not only by his reason, but by this singular passion from",
		testOutString = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz",
		b64EncodingString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	vector<unsigned char> testIn = vector<unsigned char>(testInString.begin(), testInString.end()),
		testOut = vector<unsigned char>(testOutString.begin(), testOutString.end());
	int resultLength = calculateResultLength((int)testIn.size());
	vector<unsigned char> transformResult = vector<unsigned char>(resultLength);
	char* tmp = "    ";
#pragma omp parallel for 
	for (int i = 0; i < testIn.size() / 3; i++)
	{
		base64Transform(testIn, transformResult, (i * 3), (i * 4), b64EncodingString);
	}
	cout << testOutString << endl;
	for (auto i : transformResult)
		cout << i;
	cout << endl;//Оч странно, но всё работает так, как ожидалось

}

int main()
{
	//createLargeBook();
	//return 0;

	string inFilePath = "bookForTest.txt", outFilePath = "cryptoBook.txt";
	ifstream inFile(inFilePath);
	ofstream outFile(outFilePath, std::ofstream::trunc);
	int block_size = 1024;

	while (true)
	{
		vector<char> t(block_size + 4);
		inFile.read(&t[0], block_size);
		transform(t.begin(), t.end(), t.begin(), [](char& _val) {return  --_val; });
		//transform(t.begin(), t.end(), t.begin(), op_shift_right); u can use this for decryption.
		outFile << &t[0];
		if (inFile.eof()) break;
	}
	TestFile(inFilePath, outFilePath);
	return 0;
}
//параллелить так, чтобы поток ввода, например, не работал, если поток обработки загружен. 


//TODO:Сделать обработчик для ситуации стыковки блоков текста, желательно - учитывать в будущем случай, когда обрабатываем сразу 3+блока. 
//TODO: