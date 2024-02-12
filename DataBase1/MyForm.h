#pragma once

namespace DataBase1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }
    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::FolderBrowserDialog^ PickMainFolder;
    protected:

    protected:

    private: System::Windows::Forms::Button^ FButton;
    private: System::Windows::Forms::Button^ NameFind;
    private: System::Windows::Forms::TextBox^ TextName;
    private: System::Windows::Forms::Button^ DeleteButton;
    private: System::Windows::Forms::TextBox^ TextBoxFind;
    private: System::Windows::Forms::Button^ AddButton;
    private: System::Windows::Forms::Button^ FindInBase;




    protected:

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->PickMainFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
            this->FButton = (gcnew System::Windows::Forms::Button());
            this->NameFind = (gcnew System::Windows::Forms::Button());
            this->TextName = (gcnew System::Windows::Forms::TextBox());
            this->DeleteButton = (gcnew System::Windows::Forms::Button());
            this->TextBoxFind = (gcnew System::Windows::Forms::TextBox());
            this->AddButton = (gcnew System::Windows::Forms::Button());
            this->FindInBase = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // FButton
            // 
            this->FButton->Location = System::Drawing::Point(250, 77);
            this->FButton->Name = L"FButton";
            this->FButton->Size = System::Drawing::Size(250, 126);
            this->FButton->TabIndex = 0;
            this->FButton->Text = L"Выберите папку с сотрудниками";
            this->FButton->UseVisualStyleBackColor = true;
            this->FButton->Click += gcnew System::EventHandler(this, &MyForm::FButton_Click);
            // 
            // NameFind
            // 
            this->NameFind->Location = System::Drawing::Point(12, 77);
            this->NameFind->Name = L"NameFind";
            this->NameFind->Size = System::Drawing::Size(232, 66);
            this->NameFind->TabIndex = 1;
            this->NameFind->Text = L"Поиск по Ф.И.О";
            this->NameFind->UseVisualStyleBackColor = true;
            this->NameFind->Click += gcnew System::EventHandler(this, &MyForm::NameFind_Click);
            // 
            // TextName
            // 
            this->TextName->Location = System::Drawing::Point(12, 150);
            this->TextName->Multiline = true;
            this->TextName->Name = L"TextName";
            this->TextName->Size = System::Drawing::Size(232, 53);
            this->TextName->TabIndex = 2;
            // 
            // DeleteButton
            // 
            this->DeleteButton->Location = System::Drawing::Point(506, 77);
            this->DeleteButton->Name = L"DeleteButton";
            this->DeleteButton->Size = System::Drawing::Size(215, 66);
            this->DeleteButton->TabIndex = 3;
            this->DeleteButton->Text = L"Удалить из базы работника";
            this->DeleteButton->UseVisualStyleBackColor = true;
            this->DeleteButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteButton_Click);
            // 
            // TextBoxFind
            // 
            this->TextBoxFind->Location = System::Drawing::Point(506, 150);
            this->TextBoxFind->Multiline = true;
            this->TextBoxFind->Name = L"TextBoxFind";
            this->TextBoxFind->Size = System::Drawing::Size(215, 53);
            this->TextBoxFind->TabIndex = 4;
            // 
            // AddButton
            // 
            this->AddButton->Location = System::Drawing::Point(250, 5);
            this->AddButton->Name = L"AddButton";
            this->AddButton->Size = System::Drawing::Size(250, 66);
            this->AddButton->TabIndex = 5;
            this->AddButton->Text = L"Добавить сотрудника в базу";
            this->AddButton->UseVisualStyleBackColor = true;
            this->AddButton->Click += gcnew System::EventHandler(this, &MyForm::AddButton_Click);
            // 
            // FindInBase
            // 
            this->FindInBase->Location = System::Drawing::Point(12, 5);
            this->FindInBase->Name = L"FindInBase";
            this->FindInBase->Size = System::Drawing::Size(232, 66);
            this->FindInBase->TabIndex = 6;
            this->FindInBase->Text = L"Поиск по всей базе";
            this->FindInBase->UseVisualStyleBackColor = true;
            this->FindInBase->Click += gcnew System::EventHandler(this, &MyForm::FindInBase_Click);
            // 
            // MyForm
            // 
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
            this->BackColor = System::Drawing::SystemColors::ControlDark;
            this->ClientSize = System::Drawing::Size(734, 215);
            this->Controls->Add(this->FindInBase);
            this->Controls->Add(this->AddButton);
            this->Controls->Add(this->TextBoxFind);
            this->Controls->Add(this->DeleteButton);
            this->Controls->Add(this->TextName);
            this->Controls->Add(this->NameFind);
            this->Controls->Add(this->FButton);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"MyForm";
            this->Text = L"БазаДанныхСотрудников";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void FButton_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void DataBase1::MyForm::ShowFolderDialogInThread();
    System::String^ DataBase1::MyForm::ReadPathFromXml();
    System::Void DataBase1::MyForm::SavePathToXml(String^ selectedFolder);
    private: System::Void NameFind_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void DataBase1::MyForm::FindAndDisplayInfo(String^ directoryPath, String^ targetFolderName);
    System::Void DataBase1::MyForm::UpdateUIAfterFolderSelection(String^ selectedFolder);
    System::Void DataBase1::MyForm::UpdateFButtonVisibility();
    private: System::Void DeleteButton_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void AddButton_Click(System::Object^ sender, System::EventArgs^ e);

    private: System::Void FindInBase_Click(System::Object^ sender, System::EventArgs^ e);

};
}
