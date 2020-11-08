#pragma once
#include "Juego.h"
namespace PC2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
		ControladorJuego^ juego;

	public:
		MyForm(void)
		{
			InitializeComponent();
			juego = gcnew ControladorJuego();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete juego;
		}
	private: System::Windows::Forms::Timer^ clock;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			   this->SuspendLayout();
			   // 
			   // clock
			   // 
			   this->clock->Enabled = true;
			   this->clock->Interval = 33;
			   this->clock->Tick += gcnew System::EventHandler(this, &MyForm::clock_Tick);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1832, 793);
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->MaximizeBox = false;
			   this->MinimizeBox = false;
			   this->Name = L"MyForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Mario Bros";
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			   this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			   this->ResumeLayout(false);

		   }
#pragma endregion

		   Void clock_Tick(Object^ sender, EventArgs^ e)
		   {
			   Graphics^ g = this->CreateGraphics();
			   BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
			   BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

			   bf->Graphics->Clear(Color::White);
			   juego->Mover(bf->Graphics);
			   juego->Mostrar(bf->Graphics);
			   bf->Render(g);
		   }
		   Void MyForm_KeyDown(Object^ sender, KeyEventArgs^ e)
		   {
			   juego->MovimientoJugador(true, e->KeyCode);
		   }
		   Void MyForm_KeyUp(Object^ sender, KeyEventArgs^ e)
		   {
			   juego->MovimientoJugador(false, e->KeyCode);
		   }
	};
}



