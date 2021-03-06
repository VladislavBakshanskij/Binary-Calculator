//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TButton *Calc;
	TEdit *Edit1;
	TButton *Button0;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button1;
	TButton *Button2;
	TButton *Button8;
	TButton *Button9;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TButton *ButtonDivision;
	TButton *ButtonAdd;
	TButton *ButtonSubt;
	TButton *ButtonMulti;
	TButton *ButtonCE;
	TButton *ButtonClearSymbol;
	TLabel *Label5;
	TLabel *Label6;
	void __fastcall CalcClick(TObject *Sender);
	void __fastcall Load(TObject *Sender);
	void __fastcall Close(TObject *Sender, TCloseAction &Action);
	void __fastcall Button0Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall ButtonSubtClick(TObject *Sender);
	void __fastcall ButtonDivisionClick(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonMultiClick(TObject *Sender);
	void __fastcall ButtonCEClick(TObject *Sender);
	void __fastcall ButtonClearSymbolClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};

class BinaryConverter {
private:
    //AnsiString operation =
	const int size = 16;
    AnsiString prevDigit;

	void SearchOperation(char expression){
		switch (expression) {
		case '+':MathOperation = eOperation::ADD;break;
		case '-':MathOperation = eOperation::SUBT;break;
		case '*':MathOperation = eOperation::MULTI;break;
		case '/':MathOperation = eOperation::DIVISION;break;
		}
	}

public:
	AnsiString expression;

	enum eOperation{
		NONE = 0, ADD = 1, SUBT = 2, MULTI = 3, DIVISION = 4
	}MathOperation;

	BinaryConverter(){
		MathOperation = eOperation::NONE;
		prevDigit = "";
	}

	BinaryConverter(AnsiString expression){
		this->expression = expression;
		prevDigit = "";
		MathOperation = eOperation::NONE;
	}

	AnsiString deleteMinus(AnsiString &str){
		const char *ptrStr = str.c_str();
		int length = StrLen(ptrStr);

		AnsiString temp = "";

		for (int i = 0; i < length; i++) {
			if (ptrStr[i] == '-')continue;

			temp += ptrStr[i];
		}

		return temp;
	}

	AnsiString toBinary(AnsiString &str){
		AnsiString binaryEx = "";
		const char* strBinaryEx = str.c_str();
		int length, valueEx, interger;

		if (strBinaryEx[0] == '-') {
			binaryEx = deleteMinus(str);

			length = StrLen(strBinaryEx);
			valueEx = -1 * StrToInt(binaryEx);
			interger = (int)(valueEx / 1);
		}else {
			binaryEx = str;

			length = StrLen(strBinaryEx);
			valueEx = StrToInt(binaryEx);
			interger = (int)(valueEx / 1);
		}
		binaryEx = ""; //������ ����� ��������� ����� ������
		AnsiString bin = "";

		int bitInterger[size];
		bitInterger[size - 1] = interger < 0 ? 1 : 0;

		for (int i = 0; i < size - 1; i++) {
			bitInterger[i] = interger % 2 == 0 ? 0 : 1;

			interger /= 2;
		}


		for (int i = size - 1; i >= 0; --i) {
			bin += IntToStr(bitInterger[i]);
		}

		return bin;
	}

	AnsiString toInversingBinary(AnsiString &strBinary){
		AnsiString ex = strBinary;
		const char *strBinaryEx = ex.c_str();
		//int length = StrLen(strBinaryEx);
		int binaryValue[size];

		for (int i = 0; i < size; i++) {
			binaryValue[i] = StrToInt(strBinaryEx[i]);
		}

		ex = "";

		for (int i = 0; i < size - 1; i++) {
			binaryValue[i] = binaryValue[i] == 1 ? 0 : 1;
		}

		for (int i = 0; i < size; i++) {
			if (binaryValue[i] == 1) {
				binaryValue[i] = 0;
			}else{
				binaryValue[i] = 1;
				break;
            }
		}

		for (int i = 0; i < size; i++) {
            ex += IntToStr(binaryValue[i]);
		}

		return ex;
	}

	String SearchDigit(AnsiString &expression){
		const char* exStr = expression.c_str();
		String digit = "";
		char operation[]= {"+,-,*,/"};
		int lengthOperation = StrLen(operation);

		int length = StrLen(exStr);
		int i = 0;
		bool BREAK = false;

		for (; i < length; i++) {
			String tempStr(exStr[i]);

			if (exStr[i] == '-' && i == 0) {
				digit += tempStr;
				continue;
			}

			//����� �������������� ��������
			for (int j = 0; j < lengthOperation; j++) {
				if (operation[j] == ',')continue;

				if (exStr[i] == operation[j]) {
					SearchOperation(operation[j]);
					BREAK = true;
				}
			}

			if (BREAK)break;

			digit = digit + tempStr;
		}

		if (digit == prevDigit) {
			bool CONTINUE = false;
			digit = "";

			for (; i < length; i++) {
				for (int j = 0; j < lengthOperation; j++) {
					if (operation[j] == ',')continue;

					if (exStr[i] == operation[j]){
						CONTINUE = true;
						break;
					}
				}

				if (CONTINUE) {
					CONTINUE = false;
					continue;
				}

				digit += exStr[i];
			}
		}

		prevDigit = digit;

		return digit;
	}

	int StrLen(char* str){
		int i = 0;
		while(str[i] != '\0')++i;

		return i;
	}

	int StrLen(const char* str){
		int i = 0;
		while(str[i] != '\0')++i;

		return i;
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
