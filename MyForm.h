#pragma once
#include "KarnaughMap.h" // Conecta con la lógica C++

namespace Discretas {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        int variablesSeleccionadas;

        GroupBox^ grpTabla;
        array<Label^>^ lblX;
        array<Label^>^ lblY;
        array<ComboBox^>^ cmbF;

        GroupBox^ grpMapa;
        TextBox^ txtM00; TextBox^ txtM01;
        TextBox^ txtM10; TextBox^ txtM11;

        Button^ btnCalcular;
        Button^ btnVolver;

    public:
        // Constructor que recibe el número de variables
        MyForm(int numVars)
        {
            variablesSeleccionadas = numVars;
            InitializeComponent();
            ConfigurarInterfaz(); // Dibuja todo por código

            this->Text = "Mapa de Karnaugh con " + variablesSeleccionadas + " variables";
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Size = System::Drawing::Size(750, 450);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        }

        void ConfigurarInterfaz()
        {
            // TABLA DE VERDAD
            grpTabla = gcnew GroupBox();
            grpTabla->Text = "Tabla de verdad";
            grpTabla->Location = Point(30, 30);
            grpTabla->Size = System::Drawing::Size(280, 280);
            this->Controls->Add(grpTabla);

            Label^ lblHeadX = gcnew Label(); lblHeadX->Text = "x"; lblHeadX->Location = Point(50, 40); lblHeadX->AutoSize = true;
            Label^ lblHeadY = gcnew Label(); lblHeadY->Text = "y"; lblHeadY->Location = Point(120, 40); lblHeadY->AutoSize = true;
            Label^ lblHeadF = gcnew Label(); lblHeadF->Text = "f"; lblHeadF->Location = Point(190, 40); lblHeadF->AutoSize = true;
            grpTabla->Controls->Add(lblHeadX); grpTabla->Controls->Add(lblHeadY); grpTabla->Controls->Add(lblHeadF);

            lblX = gcnew array<Label^>(4);
            lblY = gcnew array<Label^>(4);
            cmbF = gcnew array<ComboBox^>(4);

            array<String^>^ valX = { "0", "0", "1", "1" };
            array<String^>^ valY = { "0", "1", "0", "1" };

            for (int i = 0; i < 4; i++) {
                int yPos = 80 + (i * 40);

                lblX[i] = gcnew Label(); lblX[i]->Text = valX[i]; lblX[i]->Location = Point(50, yPos); lblX[i]->AutoSize = true;
                grpTabla->Controls->Add(lblX[i]);

                lblY[i] = gcnew Label(); lblY[i]->Text = valY[i]; lblY[i]->Location = Point(120, yPos); lblY[i]->AutoSize = true;
                grpTabla->Controls->Add(lblY[i]);

                cmbF[i] = gcnew ComboBox();
                cmbF[i]->Items->Add("0"); cmbF[i]->Items->Add("1");
                cmbF[i]->DropDownStyle = ComboBoxStyle::DropDownList;
                cmbF[i]->SelectedIndex = 0;
                cmbF[i]->Location = Point(175, yPos - 3); cmbF[i]->Size = System::Drawing::Size(50, 20);
                grpTabla->Controls->Add(cmbF[i]);
            }

            // MAPA DE KARNAUGH
            grpMapa = gcnew GroupBox();
            grpMapa->Text = "Mapa de Karnaugh";
            grpMapa->Location = Point(340, 30);
            grpMapa->Size = System::Drawing::Size(350, 280);
            this->Controls->Add(grpMapa);

            Label^ lblHeadYNeg = gcnew Label(); lblHeadYNeg->Text = "y'"; lblHeadYNeg->Location = Point(100, 50); lblHeadYNeg->AutoSize = true;
            Label^ lblHeadYPos = gcnew Label(); lblHeadYPos->Text = "y";  lblHeadYPos->Location = Point(160, 50); lblHeadYPos->AutoSize = true;
            grpMapa->Controls->Add(lblHeadYNeg); grpMapa->Controls->Add(lblHeadYPos);

            Label^ lblHeadXNeg = gcnew Label(); lblHeadXNeg->Text = "x'"; lblHeadXNeg->Location = Point(50, 90); lblHeadXNeg->AutoSize = true;
            Label^ lblHeadXPos = gcnew Label(); lblHeadXPos->Text = "x";  lblHeadXPos->Location = Point(50, 140); lblHeadXPos->AutoSize = true;
            grpMapa->Controls->Add(lblHeadXNeg); grpMapa->Controls->Add(lblHeadXPos);

            txtM00 = CrearCeldaMapa(90, 85); txtM01 = CrearCeldaMapa(150, 85);
            txtM10 = CrearCeldaMapa(90, 135); txtM11 = CrearCeldaMapa(150, 135);

            grpMapa->Controls->Add(txtM00); grpMapa->Controls->Add(txtM01);
            grpMapa->Controls->Add(txtM10); grpMapa->Controls->Add(txtM11);

            btnCalcular = gcnew Button();
            btnCalcular->Text = "Calcular";
            btnCalcular->Location = Point(230, 100);
            btnCalcular->Size = System::Drawing::Size(90, 40);
            btnCalcular->Click += gcnew EventHandler(this, &MyForm::btnCalcular_Click);
            grpMapa->Controls->Add(btnCalcular);

            // BOTÓN VOLVER
            btnVolver = gcnew Button();
            btnVolver->Text = "Volver";
            btnVolver->Location = Point(600, 350);
            btnVolver->Size = System::Drawing::Size(90, 30);
            btnVolver->Click += gcnew EventHandler(this, &MyForm::btnVolver_Click);
            this->Controls->Add(btnVolver);
        }

        TextBox^ CrearCeldaMapa(int posX, int posY)
        {
            TextBox^ txt = gcnew TextBox();
            txt->Location = Point(posX, posY);
            txt->Size = System::Drawing::Size(40, 25);
            txt->ReadOnly = true;
            txt->TextAlign = HorizontalAlignment::Center;
            return txt;
        }

        void btnCalcular_Click(Object^ sender, EventArgs^ e)
        {
            KarnaughMap* mapa = new KarnaughMap();

            int f00 = System::Convert::ToInt32(cmbF[0]->SelectedItem);
            int f01 = System::Convert::ToInt32(cmbF[1]->SelectedItem);
            int f10 = System::Convert::ToInt32(cmbF[2]->SelectedItem);
            int f11 = System::Convert::ToInt32(cmbF[3]->SelectedItem);

            mapa->configurarCelda(0, 0, f00);
            mapa->configurarCelda(0, 1, f01);
            mapa->configurarCelda(1, 0, f10);
            mapa->configurarCelda(1, 1, f11);

            txtM00->Text = mapa->obtenerValorCelda(0, 0).ToString();
            txtM01->Text = mapa->obtenerValorCelda(0, 1).ToString();
            txtM10->Text = mapa->obtenerValorCelda(1, 0).ToString();
            txtM11->Text = mapa->obtenerValorCelda(1, 1).ToString();

            delete mapa;
        }

        void btnVolver_Click(Object^ sender, EventArgs^ e)
        {
            this->Close(); // Regresa al menú
        }
    };
}