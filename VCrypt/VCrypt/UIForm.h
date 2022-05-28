#pragma once
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <vcclr.h>
#include <stdlib.h>
#include <msclr\marshal_cppstd.h>
#include "Crypt.h"

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#define SIZE1 128

namespace VCrypt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// UIForm için özet
	/// </summary>
	public ref class UIForm : public System::Windows::Forms::Form
	{
	public:
		UIForm(void)
		{
			InitializeComponent();
			//
			//TODO: Oluþturucu kodunu buraya ekle
			//
		}

	protected:
		/// <summary>
		///Kullanýlan tüm kaynaklarý temizleyin.
		/// </summary>
		~UIForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::TextBox^  textBox1;


	private: System::Windows::Forms::Button^  button1;








	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox2;








	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::RichTextBox^  richTextBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Button^ button3;





	private:
		/// <summary>
		///Gerekli tasarýmcý deðiþkeni.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Tasarýmcý desteði için gerekli metot - bu metodun 
		///içeriðini kod düzenleyici ile deðiþtirmeyin.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 22);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(475, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &UIForm::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(493, 20);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(132, 22);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Encrypt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UIForm::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 48);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(475, 20);
			this->textBox2->TabIndex = 14;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(493, 48);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(278, 70);
			this->richTextBox1->TabIndex = 15;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(493, 206);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(278, 70);
			this->richTextBox2->TabIndex = 26;
			this->richTextBox2->Text = L"";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(493, 178);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 22);
			this->button2->TabIndex = 17;
			this->button2->Text = L"Decrypt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &UIForm::button2_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(12, 180);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(475, 20);
			this->textBox3->TabIndex = 16;
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// richTextBox3
			// 
			this->richTextBox3->Location = System::Drawing::Point(860, 93);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->Size = System::Drawing::Size(278, 70);
			this->richTextBox3->TabIndex = 27;
			this->richTextBox3->Text = L"";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(12, 206);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(475, 20);
			this->textBox4->TabIndex = 28;
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(860, 20);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(278, 20);
			this->textBox5->TabIndex = 29;
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(1144, 20);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(132, 22);
			this->button3->TabIndex = 30;
			this->button3->Text = L"Get Decimal";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &UIForm::button3_Click);
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1305, 527);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->richTextBox3);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"UIForm";
			this->Text = L"UIForm";
			this->ResumeLayout(false);
			this->PerformLayout();
			textBox1->Text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry.";
			textBox2->Text = "aaawwwqqqxxxcccd";
			textBox4->Text = "aaawwwqqqxxxcccd";
		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		richTextBox1->Clear();
		textBox3->Clear();
		String^ inputText;
		String^ keyText;
		inputText = textBox1->Text;
		keyText = textBox2->Text;
		msclr::interop::marshal_context context;
		std::string input = context.marshal_as<std::string>(inputText);
		std::string key = context.marshal_as<std::string>(keyText);
		String^ encrypt;
		int outputSize = 0;
		int remainderMod16 = input.length();
		remainderMod16 %= 16;
		if (remainderMod16 == 0)
			outputSize = input.length();
		else
		{
			outputSize = input.length() + (16 - remainderMod16);
		}
		int** encryptedBinary = CreateNewArray(encryptedBinary, outputSize);
		encryptedBinary = GetInputTextForEncryption(input, key);
		int* encryptedDecimal = (int*)malloc(outputSize * 10);
		unsigned char letter;
		char* a = (char*)malloc(input.length());
		string encryptedString;
		//PrintAll(encryptedBinary, input.length());
		for (int i = 0; i < outputSize; i++)
		{
			int decimal = CalculateDecimal(encryptedBinary, i);
			letter = static_cast<unsigned char>(decimal);
			a[i] = letter;
			encryptedString += decimal;
			encryptedDecimal[i] = decimal;
			encrypt += (wchar_t)letter;
			//std::cout << decimal << "    " << encryptedDecimal[i] << endl;
		}
		for (int i = 0; i < outputSize; i++)
		{
			richTextBox1->Text += encryptedDecimal[i];
			if (i != outputSize - 1)
				richTextBox1->Text += " ";
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		richTextBox2->Clear();
		String^ cipherText;
		String^ keyText;
		cipherText = textBox3->Text;
		keyText = textBox4->Text;
		msclr::interop::marshal_context context;
		std::string binaryInput = context.marshal_as<std::string>(cipherText);
		std::string key = context.marshal_as<std::string>(keyText);
		std::string output = GetInputTextForDecryption(binaryInput, key);
		String^ outputText;
		outputText = msclr::interop::marshal_as<String^>(output);
		for (int i = 0; i < output.length(); i++)
		{
			richTextBox2->Text += outputText[i];
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		richTextBox3->Clear();
		String^ inputText;
		inputText = textBox5->Text;
		msclr::interop::marshal_context context;
		std::string input = context.marshal_as<std::string>(inputText);
		int i = 0;
		for (i = 0; i < input.length(); i++)
		{
			richTextBox3->Text += (unsigned char)input[i];
			richTextBox3->Text += " ";
		}
		while (i % 16 != 0)
		{
			richTextBox3->Text += 0;
			richTextBox3->Text += " ";
			i++;
		}
	}
	};
}
