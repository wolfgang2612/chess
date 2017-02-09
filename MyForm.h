#pragma once
#include "global.h"

namespace rubickscube {

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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(400, 400);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(600, 136);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 56);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Instantiate Game";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(521, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(613, 107);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"label2";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(791, 445);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Chess";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		static Drawing::Brush ^whiteBrush,^blackBrush;
		static Drawing::Graphics^ g;
		/*static int height = 30, width = 30;
		static int cellHt=50, cellWd=50;
		static int offsetX = 10, offsetY = 10;*/
		static Drawing::Pen ^thickPinkPen = gcnew Pen(Color::DeepPink, 3);
		static Drawing::Pen ^thickBluePen = gcnew Pen(Color::Blue, 3);
		static Drawing::Pen ^thickRedPen = gcnew Pen(Color::Red, 3);
		array<Int32^, 2>^ board = gcnew array<Int32^, 2>(8, 8);

	static void drawBoard()
		{
			for (int i = 0;i < 8;i++)
			{
				for (int j = 0;j < 8;j++)
				{
					if (!((i + j) % 2))
					{
						Drawing::Rectangle whiteRect(cellWd*i, cellHt*j, cellWd, cellHt);
						g->FillRectangle(whiteBrush, whiteRect);
					}

					else
					{
						Drawing::Rectangle blackRect(cellWd*i, cellHt*j, cellWd, cellHt);
						g->FillRectangle(blackBrush, blackRect);
					}
				}
			}
		}

	ref class pawn
	{
		static Drawing::Icon^ blPawnIcon = gcnew Drawing::Icon("blPawn.ico");
		static Drawing::Icon^ wPawnIcon = gcnew Drawing::Icon("wPawn.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");

	public:
		int x, y, color, alive;
		bool first;

		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wPawnIcon;
				else return blPawnIcon;
			}
			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		pawn(int a,int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}
		
		void firstClickBlack(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect; int temp2;

			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;
			temp2 = (int)board->GetValue(x, y + 1);
			if (temp2 == 0)
			{
				rect = Rectangle((x)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
				g->DrawRectangle(thickBluePen, rect);

				temp2 = (int)board->GetValue(x, y + 2);
				if (y == 1 && !temp2)
				{
					rect = Rectangle((x)*cellWd + 1, (2 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
					first = true;
				}
			}
			if (x != 7)
			{
				temp2 = (int)board->GetValue(x + 1, y + 1);
				if (temp2 > 16)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
			if (x != 0)
			{
				temp2 = (int)board->GetValue(x - 1, y + 1);
				if (temp2 > 16)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
		}

		void firstClickWhite(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;int temp2;
			rect = Rectangle((x)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;
			temp2 = (int)board->GetValue(x, y - 1);
			if (temp2 == 0)
			{
				rect = Rectangle((x)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
				g->DrawRectangle(thickBluePen, rect);

				temp2 = (int)board->GetValue(x, y - 2);
				if (y == 6 && !temp2)
				{
					rect = Rectangle((x)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
					first = true;
				}
			}
			if (x != 7)
			{
				temp2 = (int)board->GetValue(x + 1, y - 1);
				if (temp2 <= 16 && temp2 != 0)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
			if (x != 0)
			{
				temp2 = (int)board->GetValue(x - 1, y - 1);
				if (temp2 <= 16 && temp2 != 0)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
		}

		bool secondClickBlack(int xc, int yc, int temp, array<Int32^, 2>^ board,int value)
		{
			if (temp>16 && yc == (1 + y))
			{
				if (xc == x + 1)
				{
					board->SetValue(0, xc - 1, yc - 1);
					board->SetValue(value, xc, yc);
					x += 1;y += 1;
					click = 0;
					whiteTurn = true;
					return true;
				}
				else if (xc == x - 1)
				{
					board->SetValue(0, xc + 1, yc - 1);
					board->SetValue(value, xc, yc);
					x -= 1;y += 1;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			else if (yc == (1 + y) && xc == x && temp == 0)
			{
				board->SetValue(0, xc, yc - 1);
				board->SetValue(value, xc, yc);
				y += 1;
				first = false;
				click = 0;
				whiteTurn = true;
				return false;
			}
			else if (first && yc == y + 2 && temp == 0)
			{
				board->SetValue(0, xc, yc - 2);
				board->SetValue(value, xc, yc);
				y += 2;
				first = false;
				click = 0;
				whiteTurn = true;
				return false;
			}
		}

		bool secondClickWhite(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			if (temp<=16 && yc == (y-1) && temp>0)
			{
				if (xc == x + 1)
				{
					board->SetValue(0, xc - 1, yc + 1);
					board->SetValue(value, xc, yc);
					x += 1;y -= 1;
					click = 0;
					whiteTurn = false;
					return true;
				}
				else if (xc == x - 1)
				{
					board->SetValue(0, xc + 1, yc + 1);
					board->SetValue(value, xc, yc);
					x -= 1;y -= 1;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			else if (yc == (y-1) && xc == x && temp == 0)
			{
				board->SetValue(0, xc, yc + 1);
				board->SetValue(value, xc, yc);
				y -= 1;
				first = false;
				click = 0;
				whiteTurn = false;
				return false;
			}
			else if (first && yc == y - 2 && temp == 0)
			{
				board->SetValue(0, xc, yc + 2);
				board->SetValue(value, xc, yc);
				y -= 2;
				first = false;
				click = 0;
				whiteTurn = false;
				return false;
			}
		}
	};

	ref class knight
	{
		static Drawing::Icon^ blKnightIcon = gcnew Drawing::Icon("blKnight.ico");
		static Drawing::Icon^ wKnightIcon = gcnew Drawing::Icon("wKnight.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");
	public:
		int x, y, color, alive;
		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wKnightIcon;
				else return blKnightIcon;
			}
			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		knight(int a, int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}

		void firstClickBlack(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			if (x < 7 && y < 6)
			{
				if ((int)board->GetValue(x + 1, y + 2) == 0)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (2 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + 1, y + 2) > 16)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (2 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 7 && y > 1)
			{
				if ((int)board->GetValue(x + 1, y - 2) == 0)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + 1, y - 2) > 16)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 0 && y < 6)
			{
				if ((int)board->GetValue(x - 1, y + 2) == 0)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y + 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 1, y + 2) > 16)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y + 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 0 && y > 1)
			{
				if ((int)board->GetValue(x - 1, y - 2) == 0)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 1, y - 2) > 16)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 6 && y < 7)
			{
				if ((int)board->GetValue(x + 2, y + 1) == 0)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x + 2, y + 1) > 16)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 6 && y>0)
			{
				if ((int)board->GetValue(x + 2, y - 1) == 0)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x + 2, y - 1) > 16)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 1 && y < 7)
			{
				if ((int)board->GetValue(x - 2, y + 1) == 0)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 2, y + 1) > 16)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 1 && y > 0)
			{
				if ((int)board->GetValue(x - 2, y - 1) == 0)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 2, y - 1) > 16)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
		}
		void firstClickWhite(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			if (x < 7 && y < 6)
			{
				if ((int)board->GetValue(x + 1, y + 2) == 0)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (2 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + 1, y + 2) <= 16)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (2 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 7 && y > 1)
			{
				if ((int)board->GetValue(x + 1, y - 2) == 0)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + 1, y - 2) <= 16)
				{
					rect = Rectangle((x + 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 0 && y < 6)
			{
				if ((int)board->GetValue(x - 1, y + 2) == 0)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y + 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 1, y + 2) <= 16)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y + 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 0 && y > 1)
			{
				if ((int)board->GetValue(x - 1, y - 2) == 0)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 1, y - 2) <= 16)
				{
					rect = Rectangle((x - 1)*cellWd + 1, (y - 2)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 6 && y < 7)
			{
				if ((int)board->GetValue(x + 2, y + 1) == 0)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x + 2, y + 1) <= 16)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x < 6 && y>0)
			{
				if ((int)board->GetValue(x + 2, y - 1) == 0)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x + 2, y - 1) <= 16)
				{
					rect = Rectangle((x + 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 1 && y < 7)
			{
				if ((int)board->GetValue(x - 2, y + 1) == 0)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 2, y + 1) <= 16)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (1 + y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}

			if (x > 1 && y > 0)
			{
				if ((int)board->GetValue(x - 2, y - 1) == 0)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}
				else if ((int)board->GetValue(x - 2, y - 1) <= 16)
				{
					rect = Rectangle((x - 2)*cellWd + 1, (y - 1)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
				}
			}
		}
		bool secondClickBlack(int xc, int yc,int temp, array<Int32^, 2>^ board,int value)
		{
			Rectangle rect;

			if (xc == x+1 && yc == y+2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x - 1 && yc == y + 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x + 1 && yc == y - 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x - 1 && yc == y - 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x + 2 && yc == y + 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x - 2 && yc == y + 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x + 2 && yc == y - 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}

			if (xc == x - 2 && yc == y - 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) > 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = true;
					return true;
				}
			}
		}
		bool secondClickWhite(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			Rectangle rect;

			if (xc == x + 1 && yc == y + 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x - 1 && yc == y + 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x + 1 && yc == y - 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x - 1 && yc == y - 2)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x + 2 && yc == y + 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x - 2 && yc == y + 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x + 2 && yc == y - 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}

			if (xc == x - 2 && yc == y - 1)
			{
				if ((int)board->GetValue(xc, yc) == 0)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return false;
				}

				else if ((int)board->GetValue(xc, yc) <= 16)
				{
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					x = xc;
					y = yc;
					click = 0;
					whiteTurn = false;
					return true;
				}
			}
		}
	};

	ref class rook
	{
		static Drawing::Icon^ blRookIcon = gcnew Drawing::Icon("blRook.ico");
		static Drawing::Icon^ wRookIcon = gcnew Drawing::Icon("wRook.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");
	public:
		int x, y, color, alive;
		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wRookIcon;
				else return blRookIcon;
			}
			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		rook(int a, int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}

		void firstClickBlack(int temp,array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;
			
			for (int i = x-1;i >= 0;i--)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) > 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = x + 1;i <=7;i++)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) > 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) > 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y +1; i<=7; i++)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x,i) > 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		void firstClickWhite(int temp,array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			for (int i = x - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) <= 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = x + 1;i <= 7;i++)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) <= 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) <= 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y + 1; i <= 7; i++)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) <= 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		bool secondClickBlack(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			bool topkek = (xc == x && yc == y);
			int lel1;
			int lel2;
			if (!topkek)
			{
				if (temp>16 && yc==y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else if (temp > 16 && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else if (!temp && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
				
				else if (!temp && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}
		}
		bool secondClickWhite(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			bool topkek = (xc == x && yc == y);
			int lel1;
			int lel2;
			if (!topkek)
			{
				if (temp<=16 && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else if (temp <= 16 && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else if (!temp && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}

				else if (!temp && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}
		}
	};

	ref class bishop
	{
		static Drawing::Icon^ blBishopIcon = gcnew Drawing::Icon("blBishop.ico");
		static Drawing::Icon^ wBishopIcon = gcnew Drawing::Icon("wBishop.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");
	public:
		int x, y, color, alive;
		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wBishopIcon;
				else return blBishopIcon;
			}
			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		bishop(int a, int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}

		void firstClickBlack(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			for (int i = 1;i <=7-x && i<=7-y;i++)
			{
				if (!(int)board->GetValue(x+i, y+i))
				{
					rect = Rectangle((x+i)*cellWd + 1, (y+i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x+i, y+i) > 16)
				{
					rect = Rectangle((x+i)*cellWd + 1, (y+i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x - i, y + i))
				{
					rect = Rectangle((x-i)*cellWd + 1, (y+i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y + i) > 16)
				{
					rect = Rectangle((x-i)*cellWd + 1, (y+i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= 7 - x && i <= y;i++)
			{
				if (!(int)board->GetValue(x + i, y - i))
				{
					rect = Rectangle((x+i)*cellWd + 1, (y-i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y - i) > 16)
				{
					rect = Rectangle((x+i)*cellWd + 1, (y-i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= y;i++)
			{
				if (!(int)board->GetValue(x - i, y - i))
				{
					rect = Rectangle((x-i)*cellWd + 1, (y-i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y - i) > 16)
				{
					rect = Rectangle((x-i)*cellWd + 1, (y-i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		void firstClickWhite(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			for (int i = 1;i <= 7 - x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x + i, y + i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y + i) <= 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x - i, y + i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y + i) <= 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= 7 - x && i <= y;i++)
			{
				if (!(int)board->GetValue(x + i, y - i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y - i) <= 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= y;i++)
			{
				if (!(int)board->GetValue(x - i, y - i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y - i) <= 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		bool secondClickBlack(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			Rectangle rect;
			if (xc > x&&yc > y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < xc - x && i < yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc > y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < x - xc && i < yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc < y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < xc - x && i < y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc < y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < x - xc && i < y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}
		}
		bool secondClickWhite(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			Rectangle rect;
			if (xc > x&&yc > y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < xc - x && i < yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc > y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < x - xc && i < yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc < y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < xc - x && i < y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc < y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < x - xc && i < y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}
		}
	};

	ref class king
	{
		static Drawing::Icon^ blKingIcon = gcnew Drawing::Icon("blKing.ico");
		static Drawing::Icon^ wKingIcon = gcnew Drawing::Icon("wKing.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");
	public:
		int x, y, color, alive;
		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wKingIcon;
				else return blKingIcon;
			}
			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		king(int a, int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}
	};

	ref class queen
	{
		static Drawing::Icon^ blQueenIcon = gcnew Drawing::Icon("blQueen.ico");
		static Drawing::Icon^ wQueenIcon = gcnew Drawing::Icon("wQueen.ico");
		static Drawing::Icon^ wNullIcon = gcnew Drawing::Icon("wNull.ico");
		static Drawing::Icon^ bNullIcon = gcnew Drawing::Icon("blNull.ico");
	public:
		int x, y, color, alive;
		Drawing::Icon^ showIcon()
		{
			if (alive)
			{
				if (color)return wQueenIcon;
				else return blQueenIcon;
			}

			else if (!((x + y) % 2))
				return wNullIcon;
			else return bNullIcon;
		}

		queen(int a, int b, int c, int d)
		{
			x = a;
			y = b;
			color = c;
			alive = d;
		}

		void firstClickBlack(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			for (int i = x - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) > 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = x + 1;i <= 7;i++)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) > 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) > 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y + 1; i <= 7; i++)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) > 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = 1;i <= 7 - x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x + i, y + i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y + i) > 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x - i, y + i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y + i) > 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= 7 - x && i <= y;i++)
			{
				if (!(int)board->GetValue(x + i, y - i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y - i) > 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= y;i++)
			{
				if (!(int)board->GetValue(x - i, y - i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y - i) > 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		void firstClickWhite(int temp, array<Int32^, 2>^ board)
		{
			Rectangle rect;
			rect = Rectangle(x*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
			g->DrawRectangle(thickPinkPen, rect);
			click = temp;

			for (int i = x - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) <= 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = x + 1;i <= 7;i++)
			{
				if (!(int)board->GetValue(i, y))
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(i, y) <= 16)
				{
					rect = Rectangle((i)*cellWd + 1, (y)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y - 1;i >= 0;i--)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) <= 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = y + 1; i <= 7; i++)
			{
				if (!(int)board->GetValue(x, i))
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x, i) <= 16)
				{
					rect = Rectangle((x)*cellWd + 1, (i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}

			for (int i = 1;i <= 7 - x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x + i, y + i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y + i) <= 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= 7 - y;i++)
			{
				if (!(int)board->GetValue(x - i, y + i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y + i) <= 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y + i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= 7 - x && i <= y;i++)
			{
				if (!(int)board->GetValue(x + i, y - i))
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x + i, y - i) <= 16)
				{
					rect = Rectangle((x + i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
			for (int i = 1;i <= x && i <= y;i++)
			{
				if (!(int)board->GetValue(x - i, y - i))
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickBluePen, rect);
				}

				else if ((int)board->GetValue(x - i, y - i) <= 16)
				{
					rect = Rectangle((x - i)*cellWd + 1, (y - i)*cellHt + 1, cellWd - 3, cellHt - 3);
					g->DrawRectangle(thickRedPen, rect);
					break;
				}

				else break;
			}
		}
		bool secondClickBlack(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			bool topkek = (xc == x && yc == y);
			int lel1;
			int lel2;
			if (!topkek)
			{
				if (temp > 16 && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else if (temp > 16 && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else if (!temp && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}

				else if (!temp && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc > y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < xc - x && i < yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc > y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < x - xc && i < yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc < y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < xc - x && i < y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc < y)
			{
				if (temp > 16)
				{
					for (int i = 1;i < x - xc && i < y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = true;
					click = 0;
					return false;
				}
			}
		}
		bool secondClickWhite(int xc, int yc, int temp, array<Int32^, 2>^ board, int value)
		{
			bool topkek = (xc == x && yc == y);
			int lel1;
			int lel2;
			if (!topkek)
			{
				if (temp <= 16 && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else if (temp <= 16 && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else if (!temp && yc == y)
				{
					lel1 = (xc > x) ? x : xc;
					lel2 = (xc > x) ? xc : x;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(i, y))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}

				else if (!temp && xc == x)
				{
					lel1 = (yc > y) ? y : yc;
					lel2 = (yc > y) ? yc : y;
					for (int i = lel1 + 1;i < lel2;i++)
						if ((int)board->GetValue(x, i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc > y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < xc - x && i < yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= yc - y;i++)
						if ((int)board->GetValue(x + i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc > y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < x - xc && i < yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= yc - y;i++)
						if ((int)board->GetValue(x - i, y + i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc > x&&yc < y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < xc - x && i < y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= xc - x && i <= y - yc;i++)
						if ((int)board->GetValue(x + i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}

			if (xc < x&&yc < y)
			{
				if (temp <= 16)
				{
					for (int i = 1;i < x - xc && i < y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return true;
				}

				else
				{
					for (int i = 1;i <= x - xc && i <= y - yc;i++)
						if ((int)board->GetValue(x - i, y - i))return false;
					board->SetValue(0, x, y);
					board->SetValue(value, xc, yc);
					y = yc;
					x = xc;
					whiteTurn = false;
					click = 0;
					return false;
				}
			}
		}
	};

	pawn ^bPawn1 = gcnew pawn(0, 1, 0, 1); pawn ^wPawn1 = gcnew pawn(0, 6, 1, 1);
	pawn ^bPawn2 = gcnew pawn(1, 1, 0, 1); pawn ^wPawn2 = gcnew pawn(1, 6, 1, 1);
	pawn ^bPawn3 = gcnew pawn(2, 1, 0, 1); pawn ^wPawn3 = gcnew pawn(2, 6, 1, 1);
	pawn ^bPawn4 = gcnew pawn(3, 1, 0, 1); pawn ^wPawn4 = gcnew pawn(3, 6, 1, 1);
	pawn ^bPawn5 = gcnew pawn(4, 1, 0, 1); pawn ^wPawn5 = gcnew pawn(4, 6, 1, 1);
	pawn ^bPawn6 = gcnew pawn(5, 1, 0, 1); pawn ^wPawn6 = gcnew pawn(5, 6, 1, 1);
	pawn ^bPawn7 = gcnew pawn(6, 1, 0, 1); pawn ^wPawn7 = gcnew pawn(6, 6, 1, 1);
	pawn ^bPawn8 = gcnew pawn(7, 1, 0, 1); pawn ^wPawn8 = gcnew pawn(7, 6, 1, 1);

	knight ^bKn1 = gcnew knight(1, 0, 0, 1); knight ^wKn1 = gcnew knight(1, 7, 1, 1);
	knight ^bKn2 = gcnew knight(6, 0, 0, 1); knight ^wKn2 = gcnew knight(6, 7, 1, 1);

	rook ^bRook1 = gcnew rook(0, 0, 0, 1); rook ^wRook1 = gcnew rook(0, 7, 1, 1);
	rook ^bRook2 = gcnew rook(7, 0, 0, 1); rook ^wRook2 = gcnew rook(7, 7, 1, 1);

	bishop ^bBishop1 = gcnew bishop(2, 0, 0, 1); bishop ^wBishop1 = gcnew bishop(2, 7, 1, 1);
	bishop ^bBishop2 = gcnew bishop(5, 0, 0, 1); bishop ^wBishop2 = gcnew bishop(5, 7, 1, 1);

	king ^bKing = gcnew king(4, 0, 0, 1); king ^wKing = gcnew king(4, 7, 1, 1);

	queen ^bQueen = gcnew queen(3, 0, 0, 1); queen ^wQueen = gcnew queen(3, 7, 1, 1);

	void drawPieces()
	{
		Rectangle rect;
		if (bPawn1->alive) {
			rect = Rectangle(offsetX + (bPawn1->x)*cellWd, offsetY + (bPawn1->y)*cellHt, width, height);
			g->DrawIcon(bPawn1->showIcon(), rect);
		}
		if (bPawn2->alive) {
			rect = Rectangle(offsetX + (bPawn2->x)*cellWd, offsetY + (bPawn2->y)*cellHt, width, height);
			g->DrawIcon(bPawn2->showIcon(), rect);
		}
		if (bPawn3->alive) {
			rect = Rectangle(offsetX + (bPawn3->x)*cellWd, offsetY + (bPawn3->y)*cellHt, width, height);
			g->DrawIcon(bPawn3->showIcon(), rect);
		}
		if (bPawn4->alive) {
			rect = Rectangle(offsetX + (bPawn4->x)*cellWd, offsetY + (bPawn4->y)*cellHt, width, height);
			g->DrawIcon(bPawn4->showIcon(), rect);
		}
		if (bPawn5->alive) {
			rect = Rectangle(offsetX + (bPawn5->x)*cellWd, offsetY + (bPawn5->y)*cellHt, width, height);
			g->DrawIcon(bPawn5->showIcon(), rect);
		}
		if (bPawn6->alive) {
			rect = Rectangle(offsetX + (bPawn6->x)*cellWd, offsetY + (bPawn6->y)*cellHt, width, height);
			g->DrawIcon(bPawn6->showIcon(), rect);
		}
		if (bPawn7->alive) {
			rect = Rectangle(offsetX + (bPawn7->x)*cellWd, offsetY + (bPawn7->y)*cellHt, width, height);
			g->DrawIcon(bPawn7->showIcon(), rect);
		}
		if (bPawn8->alive) {
			rect = Rectangle(offsetX + (bPawn8->x)*cellWd, offsetY + (bPawn8->y)*cellHt, width, height);
			g->DrawIcon(bPawn8->showIcon(), rect);
		}

		if (wPawn1->alive) {
			rect = Rectangle(offsetX + (wPawn1->x)*cellWd, offsetY + (wPawn1->y)*cellHt, width, height);
			g->DrawIcon(wPawn1->showIcon(), rect);
		}
		if (wPawn2->alive) {
			rect = Rectangle(offsetX + (wPawn2->x)*cellWd, offsetY + (wPawn2->y)*cellHt, width, height);
			g->DrawIcon(wPawn2->showIcon(), rect);
		}
		if (wPawn3->alive) {
			rect = Rectangle(offsetX + (wPawn3->x)*cellWd, offsetY + (wPawn3->y)*cellHt, width, height);
			g->DrawIcon(wPawn3->showIcon(), rect);
		}
		if (wPawn4->alive) {
			rect = Rectangle(offsetX + (wPawn4->x)*cellWd, offsetY + (wPawn4->y)*cellHt, width, height);
			g->DrawIcon(wPawn4->showIcon(), rect);
		}
		if (wPawn5->alive) {
			rect = Rectangle(offsetX + (wPawn5->x)*cellWd, offsetY + (wPawn5->y)*cellHt, width, height);
			g->DrawIcon(wPawn5->showIcon(), rect);
		}
		if (wPawn6->alive) {
			rect = Rectangle(offsetX + (wPawn6->x)*cellWd, offsetY + (wPawn6->y)*cellHt, width, height);
			g->DrawIcon(wPawn6->showIcon(), rect);
		}
		if (wPawn7->alive) {
			rect = Rectangle(offsetX + (wPawn7->x)*cellWd, offsetY + (wPawn7->y)*cellHt, width, height);
			g->DrawIcon(wPawn7->showIcon(), rect);
		}
		if (wPawn8->alive) {
			rect = Rectangle(offsetX + (wPawn8->x)*cellWd, offsetY + (wPawn8->y)*cellHt, width, height);
			g->DrawIcon(wPawn8->showIcon(), rect);
		}

		if (bRook1->alive) {
			rect = Rectangle(offsetX + (bRook1->x)*cellWd, offsetY + (bRook1->y)*cellHt, width, height);
			g->DrawIcon(bRook1->showIcon(), rect);
		}
		if (bRook2->alive) {
			rect = Rectangle(offsetX + (bRook2->x)*cellWd, offsetY + (bRook2->y)*cellHt, width, height);
			g->DrawIcon(bRook2->showIcon(), rect);
		}
		if (wRook1->alive) {
			rect = Rectangle(offsetX + (wRook1->x)*cellWd, offsetY + (wRook1->y)*cellHt, width, height);
			g->DrawIcon(wRook1->showIcon(), rect);
		}
		if (wRook2->alive) {
			rect = Rectangle(offsetX + (wRook2->x)*cellWd, offsetY + (wRook2->y)*cellHt, width, height);
			g->DrawIcon(wRook2->showIcon(), rect);
		}

		if (bKn1->alive) {
			rect = Rectangle(offsetX + (bKn1->x)*cellWd, offsetY + (bKn1->y)*cellHt, width, height);
			g->DrawIcon(bKn1->showIcon(), rect);
		}
		if (bKn2->alive) {
			rect = Rectangle(offsetX + (bKn2->x)*cellWd, offsetY + (bKn2->y)*cellHt, width, height);
			g->DrawIcon(bKn2->showIcon(), rect);
		}
		if (wKn1->alive) {
			rect = Rectangle(offsetX + (wKn1->x)*cellWd, offsetY + (wKn1->y)*cellHt, width, height);
			g->DrawIcon(wKn1->showIcon(), rect);
		}
		if (wKn2->alive) {
			rect = Rectangle(offsetX + (wKn2->x)*cellWd, offsetY + (wKn2->y)*cellHt, width, height);
			g->DrawIcon(wKn2->showIcon(), rect);
		}

		if (bBishop1->alive) {
			rect = Rectangle(offsetX + (bBishop1->x)*cellWd, offsetY + (bBishop1->y)*cellHt, width, height);
			g->DrawIcon(bBishop1->showIcon(), rect);
		}
		if (bBishop2->alive) {
			rect = Rectangle(offsetX + (bBishop2->x)*cellWd, offsetY + (bBishop2->y)*cellHt, width, height);
			g->DrawIcon(bBishop2->showIcon(), rect);
		}
		if (wBishop1->alive) {
			rect = Rectangle(offsetX + (wBishop1->x)*cellWd, offsetY + (wBishop1->y)*cellHt, width, height);
			g->DrawIcon(wBishop1->showIcon(), rect);
		}
		if (wBishop2->alive) {
			rect = Rectangle(offsetX + (wBishop2->x)*cellWd, offsetY + (wBishop2->y)*cellHt, width, height);
			g->DrawIcon(wBishop2->showIcon(), rect);
		}

		if (bQueen->alive){
			rect = Rectangle(offsetX + (bQueen->x)*cellWd, offsetY + (bQueen->y)*cellHt, width, height);
			g->DrawIcon(bQueen->showIcon(), rect);
		}
		if (wQueen->alive) {
			rect = Rectangle(offsetX + (wQueen->x)*cellWd, offsetY + (wQueen->y)*cellHt, width, height);
			g->DrawIcon(wQueen->showIcon(), rect);
		}

		if (bKing->alive) {
			rect = Rectangle(offsetX + (bKing->x)*cellWd, offsetY + (bKing->y)*cellHt, width, height);
			g->DrawIcon(bKing->showIcon(), rect);
		}
		if (wKing->alive) {
			rect = Rectangle(offsetX + (wKing->x)*cellWd, offsetY + (wKing->y)*cellHt, width, height);
			g->DrawIcon(wKing->showIcon(), rect);
		}
	}

	void update()
	{
		pictureBox1->Refresh();
		drawBoard();
		drawPieces();
	}

	void kill(int x, int y)
	{
		if (bPawn1->x == x && bPawn1->y == y)bPawn1->alive = false;
		if (bPawn2->x == x && bPawn2->y == y)bPawn2->alive = false;
		if (bPawn3->x == x && bPawn3->y == y)bPawn3->alive = false;
		if (bPawn4->x == x && bPawn4->y == y)bPawn4->alive = false;
		if (bPawn5->x == x && bPawn5->y == y)bPawn5->alive = false;
		if (bPawn6->x == x && bPawn6->y == y)bPawn6->alive = false;
		if (bPawn7->x == x && bPawn7->y == y)bPawn7->alive = false;
		if (bPawn8->x == x && bPawn8->y == y)bPawn8->alive = false;
		if (wPawn1->x == x && wPawn1->y == y)wPawn1->alive = false;
		if (wPawn2->x == x && wPawn2->y == y)wPawn2->alive = false;
		if (wPawn3->x == x && wPawn3->y == y)wPawn3->alive = false;
		if (wPawn4->x == x && wPawn4->y == y)wPawn4->alive = false;
		if (wPawn5->x == x && wPawn5->y == y)wPawn5->alive = false;
		if (wPawn6->x == x && wPawn6->y == y)wPawn6->alive = false;
		if (wPawn7->x == x && wPawn7->y == y)wPawn7->alive = false;
		if (wPawn8->x == x && wPawn8->y == y)wPawn8->alive = false;

		if (bKn1->x == x && bKn1->y == y)bKn1->alive = false;
		if (bKn2->x == x && bKn2->y == y)bKn2->alive = false;
		if (wKn1->x == x && wKn1->y == y)wKn1->alive = false;
		if (wKn2->x == x && wKn2->y == y)wKn2->alive = false;

		if (bBishop1->x == x && bBishop1->y == y)bBishop1->alive = false;
		if (bBishop2->x == x && bBishop2->y == y)bBishop2->alive = false;
		if (wBishop1->x == x && wBishop1->y == y)wBishop1->alive = false;
		if (wBishop2->x == x && wBishop2->y == y)wBishop2->alive = false;

		if (bRook1->x == x && bRook1->y == y)bRook1->alive = false;
		if (bRook2->x == x && bRook2->y == y)bRook2->alive = false;
		if (wRook1->x == x && wRook1->y == y)wRook1->alive = false;
		if (wRook2->x == x && wRook2->y == y)wRook2->alive = false;

		if (bQueen->x == x && bQueen->y == y)bQueen->alive = false;
		if (wQueen->x == x && wQueen->y == y)wQueen->alive = false;

		if (bKing->x == x && bKing->y == y)bKing->alive = false;
		if (wKing->x == x && wKing->y == y)wKing->alive = false;
	}


private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		whiteBrush = gcnew Drawing::SolidBrush(Color::White);
		blackBrush = gcnew Drawing::SolidBrush(Color::Black);
		g = pictureBox1->CreateGraphics();
		//0 = unoccupied
		//pawn black left to right is 1-8 p1-p8				//17-24
		//black rook left is 9, right is 10	r1-r2			//25,26
		//knight left black 11, right 12 kn1-kn2			//27,28
		//bishop left black 13,right 14	bishop1-bishop2		//29,30
		//queen black 15,king 16							//31,32

		//rooks
		board->SetValue(9, 0, 0); board->SetValue(10, 7, 0);
		board->SetValue(25, 0, 7); board->SetValue(26, 7, 7);
		//knights
		board->SetValue(11, 1, 0); board->SetValue(12, 6, 0);
		board->SetValue(27, 1, 7); board->SetValue(28, 6, 7);
		//bishops
		board->SetValue(13, 2, 0); board->SetValue(14, 5, 0);
		board->SetValue(29, 2, 7); board->SetValue(30, 5, 7);
		//queen and king
		board->SetValue(15, 3, 0); board->SetValue(16, 4, 0);
		board->SetValue(31, 3, 7); board->SetValue(32, 4, 7);
		//pawns
		board->SetValue(1, 0, 1); board->SetValue(5, 4, 1);
		board->SetValue(2, 1, 1); board->SetValue(6, 5, 1);
		board->SetValue(3, 2, 1); board->SetValue(7, 6, 1);
		board->SetValue(4, 3, 1); board->SetValue(8, 7, 1);

		board->SetValue(17, 0, 6); board->SetValue(21, 4, 6);
		board->SetValue(18, 1, 6); board->SetValue(22, 5, 6);
		board->SetValue(19, 2, 6); board->SetValue(23, 6, 6);
		board->SetValue(20, 3, 6); board->SetValue(24, 7, 6);
		//rest unoccupied
		for (int i = 0;i < 4;i++)
			for (int j = 0;j < 8;j++)
				board->SetValue(0, j, i + 2);
	}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		update();
		button1->Enabled = false;
	}

private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	int mouseX = MousePosition.X - Form::Location.X - pictureBox1->Location.X - 8;
	int mouseY = MousePosition.Y - Form::Location.Y - pictureBox1->Location.X - 31;
	int xCell = mouseX / cellWd;
	int yCell = mouseY / cellHt;
	int temp = (int)board->GetValue(xCell, yCell);
	bool kek1 = (temp > 0 && temp <= 16 && click >0 && click <=16);
	bool kek2 = (temp > 16 && temp < 33 && click>16 && click <33);

	if (kek1 || kek2 || !click)
	{
		if (!whiteTurn)
		{
			switch (temp)
			{
			case 1:
				update();
				bPawn1->firstClickBlack(temp, board);
				break;

			case 2:
				update();
				bPawn2->firstClickBlack(temp, board);
				break;
			case 3:
				update();
				bPawn3->firstClickBlack(temp, board);
				break;
			case 4:
				update();
				bPawn4->firstClickBlack(temp, board);
				break;
			case 5:
				update();
				bPawn5->firstClickBlack(temp, board);
				break;
			case 6:
				update();
				bPawn6->firstClickBlack(temp, board);
				break;
			case 7:
				update();
				bPawn7->firstClickBlack(temp, board);
				break;
			case 8:
				update();
				bPawn8->firstClickBlack(temp, board);
				break;
			case 9:
				update();
				bRook1->firstClickBlack(temp,board);
				break;
			case 10:
				update();
				bRook2->firstClickBlack(temp,board);
				break;
			case 11:
				update();
				bKn1->firstClickBlack(temp,board);
				break;
			case 12:
				update();
				bKn2->firstClickBlack(temp, board);
				break;
			case 13:
				update();
				bBishop1->firstClickBlack(temp, board);
				break;
			case 14:
				update();
				bBishop2->firstClickBlack(temp, board);
				break;
			case 15:
				update();
				bQueen->firstClickBlack(temp, board);
				break;
			}
		}
		else
		{
			switch (temp)
			{
			case 17:
				update();
				wPawn1->firstClickWhite(temp, board);
				break;
			case 18:
				update();
				wPawn2->firstClickWhite(temp, board);
				break;
			case 19:
				update();
				wPawn3->firstClickWhite(temp, board);
				break;
			case 20:
				update();
				wPawn4->firstClickWhite(temp, board);
				break;
			case 21:
				update();
				wPawn5->firstClickWhite(temp, board);
				break;
			case 22:
				update();
				wPawn6->firstClickWhite(temp, board);
				break;
			case 23:
				update();
				wPawn7->firstClickWhite(temp, board);
				break;
			case 24:
				update();
				wPawn8->firstClickWhite(temp, board);
				break;
			case 25:
				update();
				wRook1->firstClickWhite(temp,board);
				break;
			case 26:
				update();
				wRook2->firstClickWhite(temp,board);
				break;
			case 27:
				update();
				wKn1->firstClickWhite(temp, board);
				break;
			case 28:
				update();
				wKn2->firstClickWhite(temp, board);
				break;
			case 29:
				update();
				wBishop1->firstClickWhite(temp, board);
				break;
			case 30:
				update();
				wBishop2->firstClickWhite(temp, board);
				break;
			case 31:
				update();
				wQueen->firstClickWhite(temp, board);
				break;
			}
		}
		
	}

	else
	{
		label1->Text = temp.ToString();
		if (!whiteTurn)
		{
			switch (click)
			{
			case 1:
				if (bPawn1->secondClickBlack(xCell, yCell, temp, board, 1))kill(xCell, yCell);
				bPawn1->alive = true;
				update();
				break;

			case 2:
				if (bPawn2->secondClickBlack(xCell, yCell, temp, board, 2))kill(xCell, yCell);
				bPawn2->alive = true;
				update();
				break;
			case 3:
				if (bPawn3->secondClickBlack(xCell, yCell, temp, board, 3))kill(xCell, yCell);
				bPawn3->alive = true;
				update();
				break;
			case 4:
				if (bPawn4->secondClickBlack(xCell, yCell, temp, board, 4))kill(xCell, yCell);
				bPawn4->alive = true;
				update();
				break;
			case 5:
				if (bPawn5->secondClickBlack(xCell, yCell, temp, board, 5))kill(xCell, yCell);
				bPawn5->alive = true;
				update();
				break;
			case 6:
				if (bPawn6->secondClickBlack(xCell, yCell, temp, board, 6))kill(xCell, yCell);
				bPawn6->alive = true;
				update();
				break;
			case 7:
				if (bPawn7->secondClickBlack(xCell, yCell, temp, board, 7))kill(xCell, yCell);
				bPawn7->alive = true;
				update();
				break;
			case 8:
				if (bPawn8->secondClickBlack(xCell, yCell, temp, board, 8))kill(xCell, yCell);
				bPawn8->alive = true;
				update();
				break;
			case 9:
				if (bRook1->secondClickBlack(xCell, yCell, temp, board, 9))kill(xCell, yCell);
				bRook1->alive = true;
				update();
				break;
			case 10:
				if (bRook2->secondClickBlack(xCell, yCell, temp, board, 10))kill(xCell, yCell);
				bRook2->alive = true;
				update();
				break;
			case 11:
				if (bKn1->secondClickBlack(xCell, yCell, temp, board, 11))kill(xCell, yCell);
				bKn1->alive = true;
				update();
				break;
			case 12:
				if (bKn2->secondClickBlack(xCell, yCell, temp, board, 12))kill(xCell, yCell);
				bKn2->alive = true;
				update();
				break;
			case 13:
				if (bBishop1->secondClickBlack(xCell, yCell, temp, board, 13))kill(xCell, yCell);
				bBishop1->alive = true;
				update();
				break;
			case 14:
				if (bBishop2->secondClickBlack(xCell, yCell, temp, board, 14))kill(xCell, yCell);
				bBishop2->alive = true;
				update();
				break;
			case 15:
				if (bQueen->secondClickBlack(xCell, yCell, temp, board, 15))kill(xCell, yCell);
				bQueen->alive = true;
				update();
				break;
			}
		}
		else
		{
			switch (click)
			{
			case 17:
				if (wPawn1->secondClickWhite(xCell, yCell, temp, board, 17))kill(xCell, yCell);
				wPawn1->alive = true;
				update();
				break;
			case 18:
				if (wPawn2->secondClickWhite(xCell, yCell, temp, board, 18))kill(xCell, yCell);
				wPawn2->alive = true;
				update();
				break;
			case 19:
				if (wPawn3->secondClickWhite(xCell, yCell, temp, board, 19))kill(xCell, yCell);
				wPawn3->alive = true;
				update();
				break;
			case 20:
				if (wPawn4->secondClickWhite(xCell, yCell, temp, board, 20))kill(xCell, yCell);
				wPawn4->alive = true;
				update();
				break;
			case 21:
				if (wPawn5->secondClickWhite(xCell, yCell, temp, board, 21))kill(xCell, yCell);
				wPawn5->alive = true;
				update();
				break;
			case 22:
				if (wPawn6->secondClickWhite(xCell, yCell, temp, board, 22))kill(xCell, yCell);
				wPawn6->alive = true;
				update();
				break;
			case 23:
				if (wPawn7->secondClickWhite(xCell, yCell, temp, board, 23))kill(xCell, yCell);
				wPawn7->alive = true;
				update();
				break;
			case 24:
				if (wPawn8->secondClickWhite(xCell, yCell, temp, board, 24))kill(xCell, yCell);
				wPawn8->alive = true;
				update();
				break;
			case 25:
				if (wRook1->secondClickWhite(xCell,yCell,temp,board,25))kill(xCell, yCell);
				wRook1->alive = true;
				update();
				break;
			case 26:
				if (wRook2->secondClickWhite(xCell, yCell, temp, board, 26))kill(xCell, yCell);
				wRook2->alive = true;
				update();
				break;
			case 27:
				if (wKn1->secondClickWhite(xCell, yCell, temp, board, 27))kill(xCell, yCell);
				wKn1->alive = true;
				update();
				break;
			case 28:
				if (wKn2->secondClickWhite(xCell, yCell, temp, board, 28))kill(xCell, yCell);
				wKn2->alive = true;
				update();
				break;
			case 29:
				if (wBishop1->secondClickWhite(xCell, yCell, temp, board, 29))kill(xCell, yCell);
				wBishop1->alive = true;
				update();
				break;
			case 30:
				if (wBishop2->secondClickWhite(xCell, yCell, temp, board, 30))kill(xCell, yCell);
				wBishop2->alive = true;
				update();
				break;
			case 31:
				if (wQueen->secondClickWhite(xCell, yCell, temp, board, 31))kill(xCell, yCell);
				wQueen->alive = true;
				update();
				break;
			}
		}
		
	}
}
};
}
