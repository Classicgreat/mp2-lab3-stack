#pragma once
#include "include\calculator.h"
#include <msclr/marshal_cppstd.h>

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ equals;
	private: System::Windows::Forms::TextBox^ math_str_input;
	private: System::Windows::Forms::Label^ result;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->equals = (gcnew System::Windows::Forms::Button());
			this->math_str_input = (gcnew System::Windows::Forms::TextBox());
			this->result = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// equals
			// 
			this->equals->Cursor = System::Windows::Forms::Cursors::Hand;
			this->equals->Location = System::Drawing::Point(234, 46);
			this->equals->Name = L"equals";
			this->equals->Size = System::Drawing::Size(38, 20);
			this->equals->TabIndex = 0;
			this->equals->Text = L"=";
			this->equals->UseVisualStyleBackColor = true;
			this->equals->Click += gcnew System::EventHandler(this, &MyForm::equals_Click);
			// 
			// math_str_input
			// 
			this->math_str_input->Location = System::Drawing::Point(12, 46);
			this->math_str_input->Name = L"math_str_input";
			this->math_str_input->Size = System::Drawing::Size(192, 20);
			this->math_str_input->TabIndex = 1;
			this->math_str_input->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::math_str_input_KeyPress);
			// 
			// result
			// 
			this->result->AutoSize = true;
			this->result->Location = System::Drawing::Point(12, 90);
			this->result->Name = L"result";
			this->result->Size = System::Drawing::Size(0, 13);
			this->result->TabIndex = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 135);
			this->Controls->Add(this->result);
			this->Controls->Add(this->math_str_input);
			this->Controls->Add(this->equals);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	void show_result() {
		TextBox^ tb = dynamic_cast<TextBox^>(math_str_input);
		if (tb != nullptr)
		{
			Calculator c;
			std::string math_str = msclr::interop::marshal_as<std::string>(tb->Text);
			std::string text;
			try {
				double res = c.eval(math_str);
				text = std::to_string(res);
			}
			catch (...) {
				text = "err";
			}
			result->Text = gcnew System::String(text.c_str());
		}
	}
	private: System::Void math_str_input_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)13)
		{
			show_result();
		}
	}
	private: System::Void equals_Click(System::Object^ sender, System::EventArgs^ e) {
		show_result();
	}
};
}
