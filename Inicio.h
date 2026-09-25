#pragma once
#include "MyForm.h" // Conecta con el formulario del mapa

namespace Discretas {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Inicio : public System::Windows::Forms::Form
    {
    private:
        Label^ lblTitulo;
        ComboBox^ comboBox1;
        Button^ button1;

    public:
        Inicio(void)
        {
            InitializeComponent();
            ConfigurarInterfaz(); // Dibuja la interfaz por código
        }

    protected:
        ~Inicio()
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
            this->Size = System::Drawing::Size(400, 300);
            this->Text = L"Menú Principal - Discretas";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        }

        void ConfigurarInterfaz()
        {
            // Imagen de fondo
            try {
                this->BackgroundImage = Image::FromFile("watermarked_img_6033019567896508837.jpg");
                this->BackgroundImageLayout = ImageLayout::Stretch;
            }
            catch (...) {
                this->BackColor = SystemColors::ControlDark;
            }

            lblTitulo = gcnew Label();
            lblTitulo->Text = "Selecciona el número de variables:";
            lblTitulo->Location = Point(90, 50);
            lblTitulo->AutoSize = true;
            lblTitulo->BackColor = Color::Transparent;
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            this->Controls->Add(lblTitulo);

            comboBox1 = gcnew ComboBox();
            comboBox1->Items->Add("2 Variables (A, B)");
            comboBox1->Items->Add("3 Variables (A, B, C)");
            comboBox1->Items->Add("4 Variables (A, B, C, D)");
            comboBox1->SelectedIndex = 0;
            comboBox1->DropDownStyle = ComboBoxStyle::DropDownList;
            comboBox1->Location = Point(100, 90);
            comboBox1->Size = System::Drawing::Size(180, 20);
            this->Controls->Add(comboBox1);

            button1 = gcnew Button();
            button1->Text = "Iniciar";
            button1->Location = Point(140, 150);
            button1->Size = System::Drawing::Size(100, 40);
            button1->BackColor = Color::LightSteelBlue;
            button1->Click += gcnew EventHandler(this, &Inicio::button1_Click);
            this->Controls->Add(button1);
        }

        void button1_Click(Object^ sender, EventArgs^ e)
        {
            int numVariables = comboBox1->SelectedIndex + 2;
            MyForm^ ventanaMapa = gcnew MyForm(numVariables);

            this->Hide();
            ventanaMapa->ShowDialog();
            this->Show();
        }
    };
}