namespace FracMaster
{
    partial class MDIForm
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.testFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrotFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.juliaFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newtonFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildInFractalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newtonFractal01ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrot01ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.arrangeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cascadedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileHorizontalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileVerticalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutFracMasterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrot02ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrot03ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.julia01ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrot04ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mandelbrot05ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.windowsToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(668, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.loadFractalToolStripMenuItem,
            this.buildInFractalToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testFractalToolStripMenuItem,
            this.mandelbrotFractalToolStripMenuItem,
            this.juliaFractalToolStripMenuItem,
            this.newtonFractalToolStripMenuItem});
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // testFractalToolStripMenuItem
            // 
            this.testFractalToolStripMenuItem.Enabled = false;
            this.testFractalToolStripMenuItem.Name = "testFractalToolStripMenuItem";
            this.testFractalToolStripMenuItem.Size = new System.Drawing.Size(264, 22);
            this.testFractalToolStripMenuItem.Text = "Test Fractal";
            this.testFractalToolStripMenuItem.Visible = false;
            this.testFractalToolStripMenuItem.Click += new System.EventHandler(this.testFractalToolStripMenuItem_Click);
            // 
            // mandelbrotFractalToolStripMenuItem
            // 
            this.mandelbrotFractalToolStripMenuItem.Name = "mandelbrotFractalToolStripMenuItem";
            this.mandelbrotFractalToolStripMenuItem.Size = new System.Drawing.Size(264, 22);
            this.mandelbrotFractalToolStripMenuItem.Text = "Mandelbrot Fractal";
            this.mandelbrotFractalToolStripMenuItem.Click += new System.EventHandler(this.mandelbrotFractalToolStripMenuItem_Click);
            // 
            // juliaFractalToolStripMenuItem
            // 
            this.juliaFractalToolStripMenuItem.Name = "juliaFractalToolStripMenuItem";
            this.juliaFractalToolStripMenuItem.Size = new System.Drawing.Size(264, 22);
            this.juliaFractalToolStripMenuItem.Text = "Julia Fractal";
            this.juliaFractalToolStripMenuItem.Click += new System.EventHandler(this.juliaFractalToolStripMenuItem_Click);
            // 
            // newtonFractalToolStripMenuItem
            // 
            this.newtonFractalToolStripMenuItem.Name = "newtonFractalToolStripMenuItem";
            this.newtonFractalToolStripMenuItem.Size = new System.Drawing.Size(264, 22);
            this.newtonFractalToolStripMenuItem.Text = "Newton Fractal - Iterations Required";
            this.newtonFractalToolStripMenuItem.Click += new System.EventHandler(this.newtonFractalToolStripMenuItem_Click);
            // 
            // loadFractalToolStripMenuItem
            // 
            this.loadFractalToolStripMenuItem.Name = "loadFractalToolStripMenuItem";
            this.loadFractalToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.loadFractalToolStripMenuItem.Text = "Load Fractal";
            this.loadFractalToolStripMenuItem.Click += new System.EventHandler(this.loadFractalToolStripMenuItem_Click);
            // 
            // buildInFractalToolStripMenuItem
            // 
            this.buildInFractalToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newtonFractal01ToolStripMenuItem,
            this.mandelbrot01ToolStripMenuItem,
            this.mandelbrot02ToolStripMenuItem,
            this.mandelbrot03ToolStripMenuItem,
            this.mandelbrot04ToolStripMenuItem,
            this.mandelbrot05ToolStripMenuItem,
            this.julia01ToolStripMenuItem});
            this.buildInFractalToolStripMenuItem.Name = "buildInFractalToolStripMenuItem";
            this.buildInFractalToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.buildInFractalToolStripMenuItem.Text = "Stock Fractals";
            // 
            // newtonFractal01ToolStripMenuItem
            // 
            this.newtonFractal01ToolStripMenuItem.Name = "newtonFractal01ToolStripMenuItem";
            this.newtonFractal01ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.newtonFractal01ToolStripMenuItem.Text = "Newton fractal 01";
            this.newtonFractal01ToolStripMenuItem.Click += new System.EventHandler(this.newtonFractal01ToolStripMenuItem_Click);
            // 
            // mandelbrot01ToolStripMenuItem
            // 
            this.mandelbrot01ToolStripMenuItem.Name = "mandelbrot01ToolStripMenuItem";
            this.mandelbrot01ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.mandelbrot01ToolStripMenuItem.Text = "Mandelbrot 01";
            this.mandelbrot01ToolStripMenuItem.Click += new System.EventHandler(this.mandelbrot01ToolStripMenuItem_Click);
            // 
            // windowsToolStripMenuItem
            // 
            this.windowsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.arrangeToolStripMenuItem});
            this.windowsToolStripMenuItem.Name = "windowsToolStripMenuItem";
            this.windowsToolStripMenuItem.Size = new System.Drawing.Size(68, 20);
            this.windowsToolStripMenuItem.Text = "Windows";
            // 
            // arrangeToolStripMenuItem
            // 
            this.arrangeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cascadedToolStripMenuItem,
            this.tileHorizontalToolStripMenuItem,
            this.tileVerticalToolStripMenuItem});
            this.arrangeToolStripMenuItem.Name = "arrangeToolStripMenuItem";
            this.arrangeToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.arrangeToolStripMenuItem.Text = "Arrange";
            // 
            // cascadedToolStripMenuItem
            // 
            this.cascadedToolStripMenuItem.Name = "cascadedToolStripMenuItem";
            this.cascadedToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.cascadedToolStripMenuItem.Text = "Cascade";
            this.cascadedToolStripMenuItem.Click += new System.EventHandler(this.cascadedToolStripMenuItem_Click);
            // 
            // tileHorizontalToolStripMenuItem
            // 
            this.tileHorizontalToolStripMenuItem.Name = "tileHorizontalToolStripMenuItem";
            this.tileHorizontalToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.tileHorizontalToolStripMenuItem.Text = "Tile Horizontal";
            this.tileHorizontalToolStripMenuItem.Click += new System.EventHandler(this.tileHorizontalToolStripMenuItem_Click);
            // 
            // tileVerticalToolStripMenuItem
            // 
            this.tileVerticalToolStripMenuItem.Name = "tileVerticalToolStripMenuItem";
            this.tileVerticalToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.tileVerticalToolStripMenuItem.Text = "Tile Vertical";
            this.tileVerticalToolStripMenuItem.Click += new System.EventHandler(this.tileVerticalToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutFracMasterToolStripMenuItem});
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // aboutFracMasterToolStripMenuItem
            // 
            this.aboutFracMasterToolStripMenuItem.Name = "aboutFracMasterToolStripMenuItem";
            this.aboutFracMasterToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
            this.aboutFracMasterToolStripMenuItem.Text = "About FracMaster";
            this.aboutFracMasterToolStripMenuItem.Click += new System.EventHandler(this.aboutFracMasterToolStripMenuItem_Click);
            // 
            // mandelbrot02ToolStripMenuItem
            // 
            this.mandelbrot02ToolStripMenuItem.Name = "mandelbrot02ToolStripMenuItem";
            this.mandelbrot02ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.mandelbrot02ToolStripMenuItem.Text = "Mandelbrot 02";
            this.mandelbrot02ToolStripMenuItem.Click += new System.EventHandler(this.mandelbrot02ToolStripMenuItem_Click);
            // 
            // mandelbrot03ToolStripMenuItem
            // 
            this.mandelbrot03ToolStripMenuItem.Name = "mandelbrot03ToolStripMenuItem";
            this.mandelbrot03ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.mandelbrot03ToolStripMenuItem.Text = "Mandelbrot 03";
            this.mandelbrot03ToolStripMenuItem.Click += new System.EventHandler(this.mandelbrot03ToolStripMenuItem_Click);
            // 
            // julia01ToolStripMenuItem
            // 
            this.julia01ToolStripMenuItem.Name = "julia01ToolStripMenuItem";
            this.julia01ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.julia01ToolStripMenuItem.Text = "Julia 01";
            this.julia01ToolStripMenuItem.Click += new System.EventHandler(this.julia01ToolStripMenuItem_Click);
            // 
            // mandelbrot04ToolStripMenuItem
            // 
            this.mandelbrot04ToolStripMenuItem.Name = "mandelbrot04ToolStripMenuItem";
            this.mandelbrot04ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.mandelbrot04ToolStripMenuItem.Text = "Mandelbrot 04";
            this.mandelbrot04ToolStripMenuItem.Click += new System.EventHandler(this.mandelbrot04ToolStripMenuItem_Click);
            // 
            // mandelbrot05ToolStripMenuItem
            // 
            this.mandelbrot05ToolStripMenuItem.Name = "mandelbrot05ToolStripMenuItem";
            this.mandelbrot05ToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.mandelbrot05ToolStripMenuItem.Text = "Mandelbrot 05";
            this.mandelbrot05ToolStripMenuItem.Click += new System.EventHandler(this.mandelbrot05ToolStripMenuItem_Click);
            // 
            // MDIForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(668, 434);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.Name = "MDIForm";
            this.Text = "FracMaster";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem testFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrotFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem juliaFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutFracMasterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newtonFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buildInFractalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newtonFractal01ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem arrangeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cascadedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tileHorizontalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tileVerticalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrot01ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrot02ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrot03ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem julia01ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrot04ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mandelbrot05ToolStripMenuItem;

    }
}

