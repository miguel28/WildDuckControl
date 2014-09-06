#pragma once

namespace SensorsSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmSim
	/// </summary>
	public ref class frmSim : public System::Windows::Forms::Form
	{
	public:
		frmSim(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			Started = false;
			AddedNoise = false;
			a = gcnew Random();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmSim()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TrackBar^  trbTarget;
	private: System::Windows::Forms::TrackBar^  trbNoise;
	protected:

	protected:

	private: System::Windows::Forms::NumericUpDown^  numStack;
	private: System::Windows::Forms::NumericUpDown^  numNoise;
	private: System::Windows::Forms::Label^  lblTarget;
	private: System::Windows::Forms::Label^  lblBaseSel;
	private: System::Windows::Forms::Label^  lblNoise;

	private: System::Windows::Forms::Label^  lblNoiseSel;
	private: System::Windows::Forms::Label^  lblStackSel;
	private: System::Windows::Forms::Button^  btnStart;
	private: System::Windows::Forms::Button^  btnSetNoise;
	private: System::Windows::Forms::Label^  lblOutput;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  lblStack;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->trbTarget = (gcnew System::Windows::Forms::TrackBar());
			this->trbNoise = (gcnew System::Windows::Forms::TrackBar());
			this->numStack = (gcnew System::Windows::Forms::NumericUpDown());
			this->numNoise = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblTarget = (gcnew System::Windows::Forms::Label());
			this->lblBaseSel = (gcnew System::Windows::Forms::Label());
			this->lblNoise = (gcnew System::Windows::Forms::Label());
			this->lblNoiseSel = (gcnew System::Windows::Forms::Label());
			this->lblStackSel = (gcnew System::Windows::Forms::Label());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnSetNoise = (gcnew System::Windows::Forms::Button());
			this->lblOutput = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblStack = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTarget))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNoise))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numStack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numNoise))->BeginInit();
			this->SuspendLayout();
			// 
			// trbTarget
			// 
			this->trbTarget->Location = System::Drawing::Point(15, 25);
			this->trbTarget->Maximum = 1700;
			this->trbTarget->Name = L"trbTarget";
			this->trbTarget->Size = System::Drawing::Size(300, 45);
			this->trbTarget->TabIndex = 0;
			this->trbTarget->Scroll += gcnew System::EventHandler(this, &frmSim::trbTarget_Scroll);
			// 
			// trbNoise
			// 
			this->trbNoise->Location = System::Drawing::Point(15, 79);
			this->trbNoise->Maximum = 100;
			this->trbNoise->Name = L"trbNoise";
			this->trbNoise->Size = System::Drawing::Size(104, 45);
			this->trbNoise->TabIndex = 1;
			this->trbNoise->Scroll += gcnew System::EventHandler(this, &frmSim::trbNoise_Scroll);
			// 
			// numStack
			// 
			this->numStack->Location = System::Drawing::Point(26, 150);
			this->numStack->Name = L"numStack";
			this->numStack->Size = System::Drawing::Size(65, 20);
			this->numStack->TabIndex = 2;
			this->numStack->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// numNoise
			// 
			this->numNoise->Location = System::Drawing::Point(350, 104);
			this->numNoise->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1500, 0, 0, 0 });
			this->numNoise->Name = L"numNoise";
			this->numNoise->Size = System::Drawing::Size(53, 20);
			this->numNoise->TabIndex = 3;
			// 
			// lblTarget
			// 
			this->lblTarget->AutoSize = true;
			this->lblTarget->Location = System::Drawing::Point(317, 21);
			this->lblTarget->Name = L"lblTarget";
			this->lblTarget->Size = System::Drawing::Size(13, 13);
			this->lblTarget->TabIndex = 4;
			this->lblTarget->Text = L"0";
			// 
			// lblBaseSel
			// 
			this->lblBaseSel->AutoSize = true;
			this->lblBaseSel->Location = System::Drawing::Point(12, 9);
			this->lblBaseSel->Name = L"lblBaseSel";
			this->lblBaseSel->Size = System::Drawing::Size(79, 13);
			this->lblBaseSel->TabIndex = 5;
			this->lblBaseSel->Text = L"Target Sensors";
			// 
			// lblNoise
			// 
			this->lblNoise->AutoSize = true;
			this->lblNoise->Location = System::Drawing::Point(125, 78);
			this->lblNoise->Name = L"lblNoise";
			this->lblNoise->Size = System::Drawing::Size(13, 13);
			this->lblNoise->TabIndex = 6;
			this->lblNoise->Text = L"0";
			// 
			// lblNoiseSel
			// 
			this->lblNoiseSel->AutoSize = true;
			this->lblNoiseSel->Location = System::Drawing::Point(12, 63);
			this->lblNoiseSel->Name = L"lblNoiseSel";
			this->lblNoiseSel->Size = System::Drawing::Size(34, 13);
			this->lblNoiseSel->TabIndex = 7;
			this->lblNoiseSel->Text = L"Noise";
			// 
			// lblStackSel
			// 
			this->lblStackSel->AutoSize = true;
			this->lblStackSel->Location = System::Drawing::Point(12, 127);
			this->lblStackSel->Name = L"lblStackSel";
			this->lblStackSel->Size = System::Drawing::Size(63, 13);
			this->lblStackSel->TabIndex = 8;
			this->lblStackSel->Text = L"Stack Lines";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(409, 43);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 9;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &frmSim::btnStart_Click);
			// 
			// btnSetNoise
			// 
			this->btnSetNoise->Location = System::Drawing::Point(409, 104);
			this->btnSetNoise->Name = L"btnSetNoise";
			this->btnSetNoise->Size = System::Drawing::Size(75, 23);
			this->btnSetNoise->TabIndex = 10;
			this->btnSetNoise->Text = L"Set Noise";
			this->btnSetNoise->UseVisualStyleBackColor = true;
			this->btnSetNoise->Click += gcnew System::EventHandler(this, &frmSim::btnSetNoise_Click);
			// 
			// lblOutput
			// 
			this->lblOutput->AutoSize = true;
			this->lblOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOutput->Location = System::Drawing::Point(499, 41);
			this->lblOutput->Name = L"lblOutput";
			this->lblOutput->Size = System::Drawing::Size(82, 25);
			this->lblOutput->TabIndex = 11;
			this->lblOutput->Text = L"Output";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &frmSim::timer1_Tick);
			// 
			// lblStack
			// 
			this->lblStack->AutoSize = true;
			this->lblStack->Location = System::Drawing::Point(279, 150);
			this->lblStack->Name = L"lblStack";
			this->lblStack->Size = System::Drawing::Size(16, 13);
			this->lblStack->TabIndex = 12;
			this->lblStack->Text = L"...";
			// 
			// frmSim
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(618, 305);
			this->Controls->Add(this->lblStack);
			this->Controls->Add(this->lblOutput);
			this->Controls->Add(this->btnSetNoise);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->lblStackSel);
			this->Controls->Add(this->lblNoiseSel);
			this->Controls->Add(this->lblNoise);
			this->Controls->Add(this->lblBaseSel);
			this->Controls->Add(this->lblTarget);
			this->Controls->Add(this->numNoise);
			this->Controls->Add(this->numStack);
			this->Controls->Add(this->trbNoise);
			this->Controls->Add(this->trbTarget);
			this->Name = L"frmSim";
			this->Text = L"frmSim";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTarget))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNoise))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numStack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numNoise))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		int stackPointer;
		float *stackBuffer;
		int STACKAVERAGE;
		float TargetBase, TNoise;
		bool Started;
		Random^ a;
		bool AddedNoise;
		void AddToStack(float range)
		{
			if (stackPointer >= STACKAVERAGE)
			{
				float *newstack = new float[STACKAVERAGE];
				int i;
				for (i = 0; i< STACKAVERAGE - 1; i++)
					newstack[i] = stackBuffer[i + 1];
				delete stackBuffer;
				stackBuffer = newstack;
				stackBuffer[STACKAVERAGE - 1] = range;
			}
			else
			{
				stackBuffer[stackPointer] = range;
				stackPointer++;
			}
		}
		float GetRange()
		{
			int i;
			float avr = 0;
			for (i = 0; i < stackPointer; i++)
			{
				avr += stackBuffer[i];
			}
			return avr / (float)stackPointer;
		}
		void ResetStack()
		{
			STACKAVERAGE = (int)numStack->Value;
			if (stackBuffer)
				delete stackBuffer;
			stackBuffer = new float[STACKAVERAGE];
			stackPointer = 0;
		}
	private: System::Void trbTarget_Scroll(System::Object^  sender, System::EventArgs^  e) {
		lblTarget->Text = ((float)(trbTarget->Value / (float)10)).ToString();
	}
	private: System::Void trbNoise_Scroll(System::Object^  sender, System::EventArgs^  e) {
		lblNoise->Text = ((float)(trbNoise->Value / (float)10)).ToString();
	}
	private: System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e) {
		Started = !Started;
		timer1->Enabled = Started;
		btnStart->Text = Started ? "Stop" : "Start";
		
		ResetStack();
		TargetBase = (float)(trbTarget->Value / (float)10);
		TNoise = (float)(trbNoise->Value / (float)10);
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		float noise = 0.0;
		if (AddedNoise)
			noise = (float)(numNoise->Value / 10);
		else
			noise= ( (a->NextDouble() -0.5f) * TNoise) + TargetBase;
		AddedNoise = false;
		AddToStack(noise);
		lblOutput->Text = GetRange().ToString();
		lblStack->Text = "";
		int i= 0;
		for (i = 0; i < stackPointer; i++)
		{
			lblStack->Text += ((float)stackBuffer[i]).ToString() + ",\r\n";
		}
			

	}
	private: System::Void btnSetNoise_Click(System::Object^  sender, System::EventArgs^  e) {
		AddedNoise = true;
	}
};
}
