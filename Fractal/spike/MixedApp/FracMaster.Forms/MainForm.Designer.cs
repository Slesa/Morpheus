namespace FracMaster.Forms
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonMandelbrot = new System.Windows.Forms.Button();
            this.buttonJulia = new System.Windows.Forms.Button();
            this.buttonNewton = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.buttonNewton01 = new System.Windows.Forms.Button();
            this.buttonMandelbrot01 = new System.Windows.Forms.Button();
            this.buttonTest = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonMandelbrot
            // 
            this.buttonMandelbrot.Location = new System.Drawing.Point(13, 13);
            this.buttonMandelbrot.Name = "buttonMandelbrot";
            this.buttonMandelbrot.Size = new System.Drawing.Size(75, 23);
            this.buttonMandelbrot.TabIndex = 0;
            this.buttonMandelbrot.Text = "Mandelbrot";
            this.buttonMandelbrot.UseVisualStyleBackColor = true;
            this.buttonMandelbrot.Click += new System.EventHandler(this.OnMandelbrot);
            // 
            // buttonJulia
            // 
            this.buttonJulia.Location = new System.Drawing.Point(95, 13);
            this.buttonJulia.Name = "buttonJulia";
            this.buttonJulia.Size = new System.Drawing.Size(75, 23);
            this.buttonJulia.TabIndex = 1;
            this.buttonJulia.Text = "Julia";
            this.buttonJulia.UseVisualStyleBackColor = true;
            this.buttonJulia.Click += new System.EventHandler(this.OnJulia);
            // 
            // buttonNewton
            // 
            this.buttonNewton.Location = new System.Drawing.Point(177, 13);
            this.buttonNewton.Name = "buttonNewton";
            this.buttonNewton.Size = new System.Drawing.Size(75, 23);
            this.buttonNewton.TabIndex = 2;
            this.buttonNewton.Text = "Newton";
            this.buttonNewton.UseVisualStyleBackColor = true;
            this.buttonNewton.Click += new System.EventHandler(this.OnNewton);
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(13, 56);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(75, 23);
            this.buttonLoad.TabIndex = 3;
            this.buttonLoad.Text = "Load...";
            this.buttonLoad.UseVisualStyleBackColor = true;
            // 
            // buttonNewton01
            // 
            this.buttonNewton01.Location = new System.Drawing.Point(13, 152);
            this.buttonNewton01.Name = "buttonNewton01";
            this.buttonNewton01.Size = new System.Drawing.Size(75, 23);
            this.buttonNewton01.TabIndex = 4;
            this.buttonNewton01.Text = "Newton 01";
            this.buttonNewton01.UseVisualStyleBackColor = true;
            // 
            // buttonMandelbrot01
            // 
            this.buttonMandelbrot01.Location = new System.Drawing.Point(13, 182);
            this.buttonMandelbrot01.Name = "buttonMandelbrot01";
            this.buttonMandelbrot01.Size = new System.Drawing.Size(75, 23);
            this.buttonMandelbrot01.TabIndex = 5;
            this.buttonMandelbrot01.Text = "Mandel 01";
            this.buttonMandelbrot01.UseVisualStyleBackColor = true;
            // 
            // buttonTest
            // 
            this.buttonTest.Location = new System.Drawing.Point(259, 13);
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Size = new System.Drawing.Size(75, 23);
            this.buttonTest.TabIndex = 6;
            this.buttonTest.Text = "Test";
            this.buttonTest.UseVisualStyleBackColor = true;
            this.buttonTest.Click += new System.EventHandler(this.OnTest);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(372, 223);
            this.Controls.Add(this.buttonTest);
            this.Controls.Add(this.buttonMandelbrot01);
            this.Controls.Add(this.buttonNewton01);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.buttonNewton);
            this.Controls.Add(this.buttonJulia);
            this.Controls.Add(this.buttonMandelbrot);
            this.Name = "MainForm";
            this.Text = "Fractal Master";
            this.Click += new System.EventHandler(this.OnTest);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonMandelbrot;
        private System.Windows.Forms.Button buttonJulia;
        private System.Windows.Forms.Button buttonNewton;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonNewton01;
        private System.Windows.Forms.Button buttonMandelbrot01;
        private System.Windows.Forms.Button buttonTest;
    }
}

