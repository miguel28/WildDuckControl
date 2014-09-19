#pragma once

namespace SensorsSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public value struct Constants3
	{
		unsigned char Prot_Medium_Limit;
		unsigned char Prot_Low_Limit;
		unsigned short Prot_High_Correction;
		unsigned short Prot_Medium_Correction;
		unsigned short Prot_Low_Correction;
	};

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
			SetConstants();
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
	private: System::Windows::Forms::GroupBox^  grpSensorsSim;
	private: System::Windows::Forms::GroupBox^  grpControlSignal;

	private: System::Windows::Forms::Label^  lblSignalValue;
	private: System::Windows::Forms::Label^  lblControlSignal;
	private: System::Windows::Forms::TrackBar^  trbControlSignal;
	private: System::Windows::Forms::Label^  lblRefuseLevel;
	private: System::Windows::Forms::Label^  lblTargetProtection;
	private: System::Windows::Forms::NumericUpDown^  numTargetProtection;
	private: System::Windows::Forms::Label^  lblError;
	private: System::Windows::Forms::Button^  btnReset;
	private: System::Windows::Forms::TrackBar^  trbControlOuput;
	private: System::Windows::Forms::Label^  lblSensorOutput2;
	private: System::Windows::Forms::TrackBar^  trbTargetSensor2;
	private: System::Windows::Forms::Label^  lblFinalOutput;
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
			this->grpSensorsSim = (gcnew System::Windows::Forms::GroupBox());
			this->lblSensorOutput2 = (gcnew System::Windows::Forms::Label());
			this->trbTargetSensor2 = (gcnew System::Windows::Forms::TrackBar());
			this->grpControlSignal = (gcnew System::Windows::Forms::GroupBox());
			this->trbControlOuput = (gcnew System::Windows::Forms::TrackBar());
			this->btnReset = (gcnew System::Windows::Forms::Button());
			this->lblError = (gcnew System::Windows::Forms::Label());
			this->lblRefuseLevel = (gcnew System::Windows::Forms::Label());
			this->lblTargetProtection = (gcnew System::Windows::Forms::Label());
			this->numTargetProtection = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblSignalValue = (gcnew System::Windows::Forms::Label());
			this->lblControlSignal = (gcnew System::Windows::Forms::Label());
			this->trbControlSignal = (gcnew System::Windows::Forms::TrackBar());
			this->lblFinalOutput = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTarget))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNoise))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numStack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numNoise))->BeginInit();
			this->grpSensorsSim->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTargetSensor2))->BeginInit();
			this->grpControlSignal->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbControlOuput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTargetProtection))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbControlSignal))->BeginInit();
			this->SuspendLayout();
			// 
			// trbTarget
			// 
			this->trbTarget->Location = System::Drawing::Point(19, 39);
			this->trbTarget->Maximum = 1700;
			this->trbTarget->Name = L"trbTarget";
			this->trbTarget->Size = System::Drawing::Size(242, 45);
			this->trbTarget->TabIndex = 0;
			this->trbTarget->Scroll += gcnew System::EventHandler(this, &frmSim::trbTarget_Scroll);
			// 
			// trbNoise
			// 
			this->trbNoise->Location = System::Drawing::Point(19, 112);
			this->trbNoise->Maximum = 100;
			this->trbNoise->Name = L"trbNoise";
			this->trbNoise->Size = System::Drawing::Size(104, 45);
			this->trbNoise->TabIndex = 1;
			this->trbNoise->Scroll += gcnew System::EventHandler(this, &frmSim::trbNoise_Scroll);
			// 
			// numStack
			// 
			this->numStack->Location = System::Drawing::Point(30, 176);
			this->numStack->Name = L"numStack";
			this->numStack->Size = System::Drawing::Size(65, 20);
			this->numStack->TabIndex = 2;
			this->numStack->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// numNoise
			// 
			this->numNoise->Location = System::Drawing::Point(307, 96);
			this->numNoise->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1500, 0, 0, 0 });
			this->numNoise->Name = L"numNoise";
			this->numNoise->Size = System::Drawing::Size(53, 20);
			this->numNoise->TabIndex = 3;
			// 
			// lblTarget
			// 
			this->lblTarget->AutoSize = true;
			this->lblTarget->Location = System::Drawing::Point(267, 39);
			this->lblTarget->Name = L"lblTarget";
			this->lblTarget->Size = System::Drawing::Size(13, 13);
			this->lblTarget->TabIndex = 4;
			this->lblTarget->Text = L"0";
			// 
			// lblBaseSel
			// 
			this->lblBaseSel->AutoSize = true;
			this->lblBaseSel->Location = System::Drawing::Point(16, 23);
			this->lblBaseSel->Name = L"lblBaseSel";
			this->lblBaseSel->Size = System::Drawing::Size(79, 13);
			this->lblBaseSel->TabIndex = 5;
			this->lblBaseSel->Text = L"Target Sensors";
			// 
			// lblNoise
			// 
			this->lblNoise->AutoSize = true;
			this->lblNoise->Location = System::Drawing::Point(129, 112);
			this->lblNoise->Name = L"lblNoise";
			this->lblNoise->Size = System::Drawing::Size(13, 13);
			this->lblNoise->TabIndex = 6;
			this->lblNoise->Text = L"0";
			// 
			// lblNoiseSel
			// 
			this->lblNoiseSel->AutoSize = true;
			this->lblNoiseSel->Location = System::Drawing::Point(16, 96);
			this->lblNoiseSel->Name = L"lblNoiseSel";
			this->lblNoiseSel->Size = System::Drawing::Size(34, 13);
			this->lblNoiseSel->TabIndex = 7;
			this->lblNoiseSel->Text = L"Noise";
			// 
			// lblStackSel
			// 
			this->lblStackSel->AutoSize = true;
			this->lblStackSel->Location = System::Drawing::Point(16, 160);
			this->lblStackSel->Name = L"lblStackSel";
			this->lblStackSel->Size = System::Drawing::Size(63, 13);
			this->lblStackSel->TabIndex = 8;
			this->lblStackSel->Text = L"Stack Lines";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(375, 39);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 9;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &frmSim::btnStart_Click);
			// 
			// btnSetNoise
			// 
			this->btnSetNoise->Location = System::Drawing::Point(375, 93);
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
			this->lblOutput->Location = System::Drawing::Point(302, 132);
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
			this->lblStack->Location = System::Drawing::Point(304, 164);
			this->lblStack->Name = L"lblStack";
			this->lblStack->Size = System::Drawing::Size(16, 13);
			this->lblStack->TabIndex = 12;
			this->lblStack->Text = L"...";
			// 
			// grpSensorsSim
			// 
			this->grpSensorsSim->Controls->Add(this->lblSensorOutput2);
			this->grpSensorsSim->Controls->Add(this->trbTargetSensor2);
			this->grpSensorsSim->Controls->Add(this->trbTarget);
			this->grpSensorsSim->Controls->Add(this->lblOutput);
			this->grpSensorsSim->Controls->Add(this->lblStack);
			this->grpSensorsSim->Controls->Add(this->btnStart);
			this->grpSensorsSim->Controls->Add(this->btnSetNoise);
			this->grpSensorsSim->Controls->Add(this->trbNoise);
			this->grpSensorsSim->Controls->Add(this->numStack);
			this->grpSensorsSim->Controls->Add(this->numNoise);
			this->grpSensorsSim->Controls->Add(this->lblBaseSel);
			this->grpSensorsSim->Controls->Add(this->lblNoiseSel);
			this->grpSensorsSim->Controls->Add(this->lblNoise);
			this->grpSensorsSim->Controls->Add(this->lblStackSel);
			this->grpSensorsSim->Controls->Add(this->lblTarget);
			this->grpSensorsSim->Location = System::Drawing::Point(12, 12);
			this->grpSensorsSim->Name = L"grpSensorsSim";
			this->grpSensorsSim->Size = System::Drawing::Size(467, 385);
			this->grpSensorsSim->TabIndex = 13;
			this->grpSensorsSim->TabStop = false;
			this->grpSensorsSim->Text = L"Sensors Simulation";
			// 
			// lblSensorOutput2
			// 
			this->lblSensorOutput2->AutoSize = true;
			this->lblSensorOutput2->Location = System::Drawing::Point(258, 203);
			this->lblSensorOutput2->Name = L"lblSensorOutput2";
			this->lblSensorOutput2->Size = System::Drawing::Size(13, 13);
			this->lblSensorOutput2->TabIndex = 14;
			this->lblSensorOutput2->Text = L"0";
			// 
			// trbTargetSensor2
			// 
			this->trbTargetSensor2->Location = System::Drawing::Point(19, 203);
			this->trbTargetSensor2->Maximum = 1700;
			this->trbTargetSensor2->Name = L"trbTargetSensor2";
			this->trbTargetSensor2->Size = System::Drawing::Size(242, 45);
			this->trbTargetSensor2->TabIndex = 13;
			this->trbTargetSensor2->Scroll += gcnew System::EventHandler(this, &frmSim::trbTargetSensor2_Scroll);
			// 
			// grpControlSignal
			// 
			this->grpControlSignal->Controls->Add(this->lblFinalOutput);
			this->grpControlSignal->Controls->Add(this->trbControlOuput);
			this->grpControlSignal->Controls->Add(this->btnReset);
			this->grpControlSignal->Controls->Add(this->lblError);
			this->grpControlSignal->Controls->Add(this->lblRefuseLevel);
			this->grpControlSignal->Controls->Add(this->lblTargetProtection);
			this->grpControlSignal->Controls->Add(this->numTargetProtection);
			this->grpControlSignal->Controls->Add(this->lblSignalValue);
			this->grpControlSignal->Controls->Add(this->lblControlSignal);
			this->grpControlSignal->Controls->Add(this->trbControlSignal);
			this->grpControlSignal->Location = System::Drawing::Point(485, 12);
			this->grpControlSignal->Name = L"grpControlSignal";
			this->grpControlSignal->Size = System::Drawing::Size(442, 249);
			this->grpControlSignal->TabIndex = 14;
			this->grpControlSignal->TabStop = false;
			this->grpControlSignal->Text = L"Control Signal";
			// 
			// trbControlOuput
			// 
			this->trbControlOuput->Location = System::Drawing::Point(85, 132);
			this->trbControlOuput->Maximum = 1022;
			this->trbControlOuput->Name = L"trbControlOuput";
			this->trbControlOuput->Size = System::Drawing::Size(291, 45);
			this->trbControlOuput->TabIndex = 8;
			this->trbControlOuput->Value = 511;
			// 
			// btnReset
			// 
			this->btnReset->Location = System::Drawing::Point(408, 13);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(28, 23);
			this->btnReset->TabIndex = 7;
			this->btnReset->Text = L"...";
			this->btnReset->UseVisualStyleBackColor = true;
			this->btnReset->Click += gcnew System::EventHandler(this, &frmSim::btnReset_Click);
			// 
			// lblError
			// 
			this->lblError->AutoSize = true;
			this->lblError->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblError->ForeColor = System::Drawing::Color::Red;
			this->lblError->Location = System::Drawing::Point(231, 68);
			this->lblError->Name = L"lblError";
			this->lblError->Size = System::Drawing::Size(20, 16);
			this->lblError->TabIndex = 6;
			this->lblError->Text = L"...";
			// 
			// lblRefuseLevel
			// 
			this->lblRefuseLevel->AutoSize = true;
			this->lblRefuseLevel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRefuseLevel->Location = System::Drawing::Point(356, 68);
			this->lblRefuseLevel->Name = L"lblRefuseLevel";
			this->lblRefuseLevel->Size = System::Drawing::Size(20, 16);
			this->lblRefuseLevel->TabIndex = 5;
			this->lblRefuseLevel->Text = L"...";
			// 
			// lblTargetProtection
			// 
			this->lblTargetProtection->AutoSize = true;
			this->lblTargetProtection->Location = System::Drawing::Point(6, 66);
			this->lblTargetProtection->Name = L"lblTargetProtection";
			this->lblTargetProtection->Size = System::Drawing::Size(89, 13);
			this->lblTargetProtection->TabIndex = 4;
			this->lblTargetProtection->Text = L"Target Protection";
			// 
			// numTargetProtection
			// 
			this->numTargetProtection->Location = System::Drawing::Point(105, 64);
			this->numTargetProtection->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->numTargetProtection->Name = L"numTargetProtection";
			this->numTargetProtection->Size = System::Drawing::Size(76, 20);
			this->numTargetProtection->TabIndex = 3;
			this->numTargetProtection->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			// 
			// lblSignalValue
			// 
			this->lblSignalValue->AutoSize = true;
			this->lblSignalValue->Location = System::Drawing::Point(383, 17);
			this->lblSignalValue->Name = L"lblSignalValue";
			this->lblSignalValue->Size = System::Drawing::Size(25, 13);
			this->lblSignalValue->TabIndex = 2;
			this->lblSignalValue->Text = L"511";
			// 
			// lblControlSignal
			// 
			this->lblControlSignal->AutoSize = true;
			this->lblControlSignal->Location = System::Drawing::Point(7, 23);
			this->lblControlSignal->Name = L"lblControlSignal";
			this->lblControlSignal->Size = System::Drawing::Size(72, 13);
			this->lblControlSignal->TabIndex = 1;
			this->lblControlSignal->Text = L"Control Signal";
			// 
			// trbControlSignal
			// 
			this->trbControlSignal->Location = System::Drawing::Point(85, 17);
			this->trbControlSignal->Maximum = 1022;
			this->trbControlSignal->Name = L"trbControlSignal";
			this->trbControlSignal->Size = System::Drawing::Size(291, 45);
			this->trbControlSignal->TabIndex = 0;
			this->trbControlSignal->Value = 511;
			this->trbControlSignal->Scroll += gcnew System::EventHandler(this, &frmSim::trbControlSignal_Scroll);
			// 
			// lblFinalOutput
			// 
			this->lblFinalOutput->AutoSize = true;
			this->lblFinalOutput->Location = System::Drawing::Point(10, 111);
			this->lblFinalOutput->Name = L"lblFinalOutput";
			this->lblFinalOutput->Size = System::Drawing::Size(87, 13);
			this->lblFinalOutput->TabIndex = 9;
			this->lblFinalOutput->Text = L"Output To NAZA";
			// 
			// frmSim
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(939, 476);
			this->Controls->Add(this->grpControlSignal);
			this->Controls->Add(this->grpSensorsSim);
			this->Name = L"frmSim";
			this->Text = L"frmSim";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTarget))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNoise))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numStack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numNoise))->EndInit();
			this->grpSensorsSim->ResumeLayout(false);
			this->grpSensorsSim->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbTargetSensor2))->EndInit();
			this->grpControlSignal->ResumeLayout(false);
			this->grpControlSignal->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbControlOuput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTargetProtection))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbControlSignal))->EndInit();
			this->ResumeLayout(false);

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
		TargetBase = (float)(trbTarget->Value / (float)10);
		TNoise = (float)(trbNoise->Value / (float)10);
	}
	private: System::Void trbNoise_Scroll(System::Object^  sender, System::EventArgs^  e) {
		lblNoise->Text = ((float)(trbNoise->Value / (float)10)).ToString();
		TargetBase = (float)(trbTarget->Value / (float)10);
		TNoise = (float)(trbNoise->Value / (float)10);
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

		float range1 = GetRange();
		float range2 = (trbTargetSensor2->Value / 10);
		int target = (int)(numTargetProtection->Value);
		int ControlSignal = trbControlSignal->Value;

		ErrorDifCalc = range1 - target;
		float ErrorDifCalc2 = range2 - target;
		lblError->Text = ErrorDifCalc.ToString() + ", " + ErrorDifCalc2.ToString();

		int final = AxisProtection(range1, range2, target, ControlSignal);

		trbControlOuput->Value = final;
	}
	private: System::Void btnSetNoise_Click(System::Object^  sender, System::EventArgs^  e) {
		AddedNoise = true;
	}


	//////////////////// Control Signal Simulation
	private: Constants3 Conts3Report;
			 int ErrorDifCalc;
			 void SetConstants()
			 {
				 Conts3Report.Prot_Medium_Limit = 20;
				 Conts3Report.Prot_Low_Limit = 12;
				 Conts3Report.Prot_High_Correction = 1000;
				 Conts3Report.Prot_Medium_Correction = 1000;
				 Conts3Report.Prot_Low_Correction = 200;
			 }

			 int CalcOposition(int range1, float target, int ControlAxis, bool *isInDanger)
			 {
				 if (ControlAxis < 0)
					 ControlAxis *= -1;

				 float Oposition = 0;
				 float Output = 0;
				 int FinalValue;

				 //// Oposition is calculated number that reduce the control signal
				 if (range1 >= target + Conts3Report.Prot_Medium_Limit)/// Positive Axis System protected
				 {
					 Oposition = 0;
					 Output = (Oposition * ControlAxis);
				 }
				 else if (range1 >= target + Conts3Report.Prot_Low_Limit)/// The system is getting closer to a wall little oposition
				 {
					 float error = range1 - Conts3Report.Prot_Low_Limit - target;
					 float maxError = Conts3Report.Prot_Medium_Limit - Conts3Report.Prot_Low_Limit;
					 float gain = 1.0f - (error / maxError);
					 float correction = (Conts3Report.Prot_Low_Correction / 1000.0f);
					 Oposition = gain * correction;

					 Output = (Oposition * ControlAxis);
				 }
				 else if (range1 >= target)/// The System is very close to the target oposition Oposition total (oposition equal to control signal)
				 {
					 float error = range1 - target;
					 float maxError = Conts3Report.Prot_Low_Limit - 0;
					 float gain = 1.0f - (error / maxError);
					 float correction = (Conts3Report.Prot_Medium_Correction / 1000.0f);
					 Oposition = gain * correction;

					 Output = (Oposition * ControlAxis);
				 }
				 else /// The sytem is in danger negative oposition.
				 {
					 float error = range1 - target;
					 float maxError = target;
					 float gain = -(error / maxError);
					 float correction = (Conts3Report.Prot_High_Correction / 1000.0f) + 1.0f;
					 Oposition = gain * correction;
					 Output = (Oposition * 511);// +ControlAxis;
					 *isInDanger = true;
				 }

				 return Output;
			 }

			 int AxisProtection(float range1, float range2, int target, int ControlSignal)
			 {
				 float Output1 = 0;
				 float Output2 = 0;
				 bool Danger1 = false;
				 bool Danger2 = false;
				 int FinalValue = 0;

				 Output1 = CalcOposition((int)range1, (int)target, ControlSignal - 511, &Danger1);
				 Output2 = CalcOposition((int)range2, (int)target, ControlSignal - 511, &Danger2);

				 FinalValue = ControlSignal;
				 if (Danger1 || Danger2)
				 {
					 FinalValue = 511;
					 if (Danger1 && Danger2)
					 {
						 Output1 /= 4;
						 Output2 /= 4;
					 }

					 if (Danger1)
						 FinalValue -= Output1;
					 if (Danger2)
						 FinalValue += Output2;
				 }
				 else
				 {
					 if (ControlSignal >= 511)
						 FinalValue = trbControlSignal->Value - Output1;
					 else
						 FinalValue = trbControlSignal->Value + Output2;
				 }

				 lblRefuseLevel->Text = Output1.ToString() + ", " + Output2.ToString();
				 if (FinalValue <= 0)
					 FinalValue = 0;
				 if (FinalValue >= 1022)
					 FinalValue = 1022;

				 return FinalValue;
			}


	private: System::Void trbControlSignal_Scroll(System::Object^  sender, System::EventArgs^  e) {
		lblSignalValue->Text = trbControlSignal->Value.ToString();
	}
	private: System::Void btnReset_Click(System::Object^  sender, System::EventArgs^  e) {
		trbControlSignal->Value = 511;

	}
	private: System::Void trbTargetSensor2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		lblSensorOutput2->Text = (trbTargetSensor2->Value/10).ToString();
	}
};
}
