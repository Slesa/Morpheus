namespace MixedApp.Forms
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
            this.buttonLeaf = new System.Windows.Forms.Button();
            this.buttonFern = new System.Windows.Forms.Button();
            this.buttonKidney = new System.Windows.Forms.Button();
            this.buttonColourTree = new System.Windows.Forms.Button();
            this.buttonRainbowFeather = new System.Windows.Forms.Button();
            this.buttonSpiralThing = new System.Windows.Forms.Button();
            this.buttonCircle = new System.Windows.Forms.Button();
            this.buttonCircles2 = new System.Windows.Forms.Button();
            this.buttonTree2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonLeaf
            // 
            this.buttonLeaf.Location = new System.Drawing.Point(12, 156);
            this.buttonLeaf.Name = "buttonLeaf";
            this.buttonLeaf.Size = new System.Drawing.Size(146, 23);
            this.buttonLeaf.TabIndex = 5;
            this.buttonLeaf.Text = "Leaf";
            this.buttonLeaf.UseVisualStyleBackColor = true;
            this.buttonLeaf.Click += new System.EventHandler(this.OnLeaf);
            // 
            // buttonFern
            // 
            this.buttonFern.Location = new System.Drawing.Point(12, 98);
            this.buttonFern.Name = "buttonFern";
            this.buttonFern.Size = new System.Drawing.Size(146, 23);
            this.buttonFern.TabIndex = 3;
            this.buttonFern.Text = "Fern";
            this.buttonFern.UseVisualStyleBackColor = true;
            this.buttonFern.Click += new System.EventHandler(this.OnFern);
            // 
            // buttonKidney
            // 
            this.buttonKidney.Location = new System.Drawing.Point(12, 127);
            this.buttonKidney.Name = "buttonKidney";
            this.buttonKidney.Size = new System.Drawing.Size(146, 23);
            this.buttonKidney.TabIndex = 4;
            this.buttonKidney.Text = "Kidney";
            this.buttonKidney.UseVisualStyleBackColor = true;
            this.buttonKidney.Click += new System.EventHandler(this.OnKidney);
            // 
            // buttonColourTree
            // 
            this.buttonColourTree.Location = new System.Drawing.Point(12, 69);
            this.buttonColourTree.Name = "buttonColourTree";
            this.buttonColourTree.Size = new System.Drawing.Size(146, 23);
            this.buttonColourTree.TabIndex = 2;
            this.buttonColourTree.Text = "Colour Tree";
            this.buttonColourTree.UseVisualStyleBackColor = true;
            this.buttonColourTree.Click += new System.EventHandler(this.OnColourTree);
            // 
            // buttonRainbowFeather
            // 
            this.buttonRainbowFeather.Location = new System.Drawing.Point(12, 185);
            this.buttonRainbowFeather.Name = "buttonRainbowFeather";
            this.buttonRainbowFeather.Size = new System.Drawing.Size(146, 23);
            this.buttonRainbowFeather.TabIndex = 6;
            this.buttonRainbowFeather.Text = "Rainbow Feather";
            this.buttonRainbowFeather.UseVisualStyleBackColor = true;
            this.buttonRainbowFeather.Click += new System.EventHandler(this.OnRainbowFeather);
            // 
            // buttonSpiralThing
            // 
            this.buttonSpiralThing.Location = new System.Drawing.Point(12, 214);
            this.buttonSpiralThing.Name = "buttonSpiralThing";
            this.buttonSpiralThing.Size = new System.Drawing.Size(146, 23);
            this.buttonSpiralThing.TabIndex = 7;
            this.buttonSpiralThing.Text = "Spiral Thing";
            this.buttonSpiralThing.UseVisualStyleBackColor = true;
            this.buttonSpiralThing.Click += new System.EventHandler(this.OnSpiralThing);
            // 
            // buttonCircle
            // 
            this.buttonCircle.Location = new System.Drawing.Point(12, 12);
            this.buttonCircle.Name = "buttonCircle";
            this.buttonCircle.Size = new System.Drawing.Size(146, 23);
            this.buttonCircle.TabIndex = 0;
            this.buttonCircle.Text = "Circles";
            this.buttonCircle.UseVisualStyleBackColor = true;
            this.buttonCircle.Click += new System.EventHandler(this.OnCircles);
            // 
            // buttonCircles2
            // 
            this.buttonCircles2.Location = new System.Drawing.Point(12, 40);
            this.buttonCircles2.Name = "buttonCircles2";
            this.buttonCircles2.Size = new System.Drawing.Size(146, 23);
            this.buttonCircles2.TabIndex = 1;
            this.buttonCircles2.Text = "Circles 2";
            this.buttonCircles2.UseVisualStyleBackColor = true;
            this.buttonCircles2.Click += new System.EventHandler(this.OnCircles2);
            // 
            // buttonTree2
            // 
            this.buttonTree2.Location = new System.Drawing.Point(196, 12);
            this.buttonTree2.Name = "buttonTree2";
            this.buttonTree2.Size = new System.Drawing.Size(120, 23);
            this.buttonTree2.TabIndex = 8;
            this.buttonTree2.Text = "Tree 2";
            this.buttonTree2.UseVisualStyleBackColor = true;
            this.buttonTree2.Click += new System.EventHandler(this.OnTree2);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(371, 271);
            this.Controls.Add(this.buttonTree2);
            this.Controls.Add(this.buttonCircles2);
            this.Controls.Add(this.buttonCircle);
            this.Controls.Add(this.buttonSpiralThing);
            this.Controls.Add(this.buttonRainbowFeather);
            this.Controls.Add(this.buttonColourTree);
            this.Controls.Add(this.buttonKidney);
            this.Controls.Add(this.buttonFern);
            this.Controls.Add(this.buttonLeaf);
            this.Name = "MainForm";
            this.Text = "Fractals";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonLeaf;
        private System.Windows.Forms.Button buttonFern;
        private System.Windows.Forms.Button buttonKidney;
        private System.Windows.Forms.Button buttonColourTree;
        private System.Windows.Forms.Button buttonRainbowFeather;
        private System.Windows.Forms.Button buttonSpiralThing;
        private System.Windows.Forms.Button buttonCircle;
        private System.Windows.Forms.Button buttonCircles2;
        private System.Windows.Forms.Button buttonTree2;
    }
}

