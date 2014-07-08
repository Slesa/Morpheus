namespace FracMaster
{
    partial class EditPaletteDialog
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
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.setAsStartIndexForGradientToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calculateGradientToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetStartIndexForGradientToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.AutoScroll = true;
            this.splitContainer1.Panel1.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.splitContainer1.Panel1.Controls.Add(this.panel1);
            this.splitContainer1.Panel1.SizeChanged += new System.EventHandler(this.splitContainer1_Panel1_SizeChanged);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.button2);
            this.splitContainer1.Panel2.Controls.Add(this.button1);
            this.splitContainer1.Size = new System.Drawing.Size(487, 377);
            this.splitContainer1.SplitterDistance = 345;
            this.splitContainer1.TabIndex = 0;
            this.splitContainer1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.Control;
            this.panel1.Location = new System.Drawing.Point(26, 38);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(275, 308);
            this.panel1.TabIndex = 0;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(28, 54);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(81, 24);
            this.button2.TabIndex = 1;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.Location = new System.Drawing.Point(28, 24);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(81, 24);
            this.button1.TabIndex = 0;
            this.button1.Text = "Ok";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.setAsStartIndexForGradientToolStripMenuItem,
            this.calculateGradientToolStripMenuItem,
            this.resetStartIndexForGradientToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(233, 92);
            // 
            // setAsStartIndexForGradientToolStripMenuItem
            // 
            this.setAsStartIndexForGradientToolStripMenuItem.Name = "setAsStartIndexForGradientToolStripMenuItem";
            this.setAsStartIndexForGradientToolStripMenuItem.Size = new System.Drawing.Size(232, 22);
            this.setAsStartIndexForGradientToolStripMenuItem.Text = "Set As Start Index For Gradient";
            this.setAsStartIndexForGradientToolStripMenuItem.Click += new System.EventHandler(this.setAsStartIndexForGradientToolStripMenuItem_Click);
            // 
            // calculateGradientToolStripMenuItem
            // 
            this.calculateGradientToolStripMenuItem.Enabled = false;
            this.calculateGradientToolStripMenuItem.Name = "calculateGradientToolStripMenuItem";
            this.calculateGradientToolStripMenuItem.Size = new System.Drawing.Size(232, 22);
            this.calculateGradientToolStripMenuItem.Text = "Calculate Gradient";
            this.calculateGradientToolStripMenuItem.Click += new System.EventHandler(this.calculateGradientToolStripMenuItem_Click);
            // 
            // resetStartIndexForGradientToolStripMenuItem
            // 
            this.resetStartIndexForGradientToolStripMenuItem.Enabled = false;
            this.resetStartIndexForGradientToolStripMenuItem.Name = "resetStartIndexForGradientToolStripMenuItem";
            this.resetStartIndexForGradientToolStripMenuItem.Size = new System.Drawing.Size(232, 22);
            this.resetStartIndexForGradientToolStripMenuItem.Text = "Reset Start Index for gradient";
            this.resetStartIndexForGradientToolStripMenuItem.Click += new System.EventHandler(this.resetStartIndexForGradientToolStripMenuItem_Click);
            // 
            // EditPaletteDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(487, 377);
            this.Controls.Add(this.splitContainer1);
            this.Name = "EditPaletteDialog";
            this.Text = "EditPaletteDialog";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem setAsStartIndexForGradientToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calculateGradientToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetStartIndexForGradientToolStripMenuItem;
    }
}