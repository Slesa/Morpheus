namespace MixedApp.Forms
{
    partial class FractalView
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
            this.buttonSettings = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonImage = new System.Windows.Forms.Button();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.groupButtons = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.groupButtons.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonSettings
            // 
            this.buttonSettings.Location = new System.Drawing.Point(6, 19);
            this.buttonSettings.Name = "buttonSettings";
            this.buttonSettings.Size = new System.Drawing.Size(75, 23);
            this.buttonSettings.TabIndex = 0;
            this.buttonSettings.Text = "Settings...";
            this.buttonSettings.UseVisualStyleBackColor = true;
            this.buttonSettings.Click += new System.EventHandler(this.OnSettings);
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(87, 19);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 1;
            this.buttonSave.Text = "Save...";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.OnSave);
            // 
            // buttonImage
            // 
            this.buttonImage.Location = new System.Drawing.Point(168, 19);
            this.buttonImage.Name = "buttonImage";
            this.buttonImage.Size = new System.Drawing.Size(75, 23);
            this.buttonImage.TabIndex = 2;
            this.buttonImage.Text = "Image...";
            this.buttonImage.UseVisualStyleBackColor = true;
            this.buttonImage.Click += new System.EventHandler(this.OnImage);
            // 
            // pictureBox
            // 
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(0, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(679, 430);
            this.pictureBox.TabIndex = 3;
            this.pictureBox.TabStop = false;
            // 
            // groupButtons
            // 
            this.groupButtons.Controls.Add(this.buttonSettings);
            this.groupButtons.Controls.Add(this.buttonSave);
            this.groupButtons.Controls.Add(this.buttonImage);
            this.groupButtons.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupButtons.Location = new System.Drawing.Point(0, 0);
            this.groupButtons.Name = "groupButtons";
            this.groupButtons.Size = new System.Drawing.Size(679, 55);
            this.groupButtons.TabIndex = 4;
            this.groupButtons.TabStop = false;
            // 
            // FractalView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(679, 430);
            this.Controls.Add(this.groupButtons);
            this.Controls.Add(this.pictureBox);
            this.Name = "FractalView";
            this.Text = "FractalView";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.groupButtons.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSettings;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonImage;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.GroupBox groupButtons;
    }
}