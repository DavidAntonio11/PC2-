#pragma once
#include <iostream>
#include <vector>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class Personajes
{
protected:
	int x, y;
	int dx, dy;
	float ancho, alto;
	int IDx;
public:
	Personajes()
	{
		x = y = 0;
		dx = dy = 0;
		ancho = alto = 0;
		IDx = 0;
	}

	int GetAncho() {
		return ancho;
	}
	int GetAlto() {
		return alto;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}


	void SetDX(int value)
	{
		dx = value;
	}
	void SetDY(int value)
	{
		dy = value;
	}

	Rectangle Area()
	{
		return Rectangle(x, y, ancho, alto);
	}
	Rectangle NextArea()
	{
		return Rectangle(x + dx, y + dy, ancho, alto);
	}

	virtual void Mover(Graphics^ g)
	{
		x += dx;
		y += dy;
	}
	virtual void Mostrar(Graphics^ g, Bitmap^ img)
	{
		g->FillRectangle(Brushes::White, Area());
	}
};

enum SpriteJugador
{

	CaminarDerecha,
	CaminarIzquierda,
	Agacharse,
	Saltar,


};

class Jugador : public Personajes
{
private:
	SpriteJugador accion;
public:
	Jugador(Bitmap^ img)
	{
		x = 1; y = 100;
		dx = dy = 0;

		ancho = img->Width /10;
		alto = img->Height*10 ;

		accion = CaminarDerecha;
	}

	void SetAccion(SpriteJugador value)
	{
		accion = value;
	}


	void Mover(Graphics^ g)
	{



		if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
			y += dy;



	}
	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);

		if (dx != 0 || dy != 0) {
			IDx = (IDx + 1) % 4;
		}
	}
};

ref class ControladorJuego
{
private:
	Jugador* jugador;
	Bitmap^ imgJugador;
public:
	ControladorJuego()
	{

		imgJugador = gcnew Bitmap("Imagenes\\MarioWalk.PNG");

		jugador = new Jugador(imgJugador);

	}
	~ControladorJuego()
	{
		delete jugador;
	}

	void MovimientoJugador(bool accion, Keys tecla)
	{
		int v = 3;

		if (accion == true)
		{
			if (tecla == Keys::Up)
			{
				jugador->SetDY(-v);
				jugador->SetAccion(Saltar);
			}
			else if (tecla == Keys::Down)
			{

				jugador->SetAccion(Agacharse);
			}
			else if (tecla == Keys::Left)
			{
				jugador->SetDX(v - 2);
				jugador->SetAccion(CaminarIzquierda);
			}
			else if (tecla == Keys::Right)
			{
				jugador->SetDX(v + 2);
				jugador->SetAccion(CaminarDerecha);
			}
		}
		else
		{
			if (tecla == Keys::Up)
				jugador->SetDY(0);
			else if (tecla == Keys::Down)
				jugador->SetDY(0);
			else if (tecla == Keys::Left)
				jugador->SetDX(0);
			else if (tecla == Keys::Right)
				jugador->SetDX(0);
		}
	}

	void Mover(Graphics^ g)
	{

		jugador->Mover(g);


	}
	void Mostrar(Graphics^ g)
	{

		jugador->Mostrar(g, imgJugador);
	}

};