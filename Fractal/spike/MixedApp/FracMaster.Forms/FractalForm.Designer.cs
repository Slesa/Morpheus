namespace FracMaster.Forms
{
    partial class FractalForm
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
            this.buttonRender = new System.Windows.Forms.Button();
            this.buttonStop = new System.Windows.Forms.Button();
            this.buttonSettings = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonSaveImage = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonRender
            // 
            this.buttonRender.Location = new System.Drawing.Point(13, 13);
            this.buttonRender.Name = "buttonRender";
            this.buttonRender.Size = new System.Drawing.Size(75, 23);
            this.buttonRender.TabIndex = 0;
            this.buttonRender.Text = "Render";
            this.buttonRender.UseVisualStyleBackColor = true;
            this.buttonRender.Click += new System.EventHandler(this.OnStartRender);
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(95, 13);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(75, 23);
            this.buttonStop.TabIndex = 1;
            this.buttonStop.Text = "Stop";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.OnStopRender);
            // 
            // buttonSettings
            // 
            this.buttonSettings.Location = new System.Drawing.Point(177, 13);
            this.buttonSettings.Name = "buttonSettings";
            this.buttonSettings.Size = new System.Drawing.Size(75, 23);
            this.buttonSettings.TabIndex = 2;
            this.buttonSettings.Text = "Settings...";
            this.buttonSettings.UseVisualStyleBackColor = true;
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(259, 13);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 3;
            this.buttonSave.Text = "Save...";
            this.buttonSave.UseVisualStyleBackColor = true;
            // 
            // buttonSaveImage
            // 
            this.buttonSaveImage.Location = new System.Drawing.Point(341, 13);
            this.buttonSaveImage.Name = "buttonSaveImage";
            this.buttonSaveImage.Size = new System.Drawing.Size(75, 23);
            this.buttonSaveImage.TabIndex = 4;
            this.buttonSaveImage.Text = "Image...";
            this.buttonSaveImage.UseVisualStyleBackColor = true;
            // 
            // FractalForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(694, 502);
            this.Controls.Add(this.buttonSaveImage);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonSettings);
            this.Controls.Add(this.buttonStop);
            this.Controls.Add(this.buttonRender);
            this.Name = "FractalForm";
            this.Text = "FractalForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonRender;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Button buttonSettings;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonSaveImage;
    }
}