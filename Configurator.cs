using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace Ngene_Configurator
{
	public partial class Configurator : Form
	{
		#region Initialization

		private const string fileDialogFilter = "configuration files (*.conf)|*.conf";
		private const string ngene_conf = "ngene.conf";
		private const string noParameters = "none";

		private string currentConfigurationFile, hint;

		public Configurator()
		{
			InitializeComponent();
			this.MaximumSize = this.Size;
			this.MinimumSize = this.Size;
		}

		private void Configurator_Load(object sender, EventArgs e)
		{
			try
			{
				LoadModules();
			}
			catch (DirectoryNotFoundException ex)
			{
				MessageBox.Show("You're not running the configurator from the same folder as Ngene.\n\nException:\n" + ex.Message, "Failed to locate modules", MessageBoxButtons.OK, MessageBoxIcon.Error);
				Application.Exit();
				return;
			}

			InitializeControllers();
			InitializeHelpers();

			try
			{
				using (StreamReader s = new StreamReader(ngene_conf))
				{
					LoadConfiguration(s);
					this.currentConfigurationFile = ngene_conf;
				}
				this.hint = "";
			}
			catch //(FileNotFoundException ex)
			{
				//MessageBox.Show("Please make sure you're running the configurator from the same folder.\n\nException:\n" + ex.Message, "Could not find default configuration", MessageBoxButtons.OK, MessageBoxIcon.Warning);
				this.currentConfigurationFile = string.Empty;
				this.hint = "No default configuration found";
				component_MouseLeave(sender, e);
			}
		}

		private void LoadModules()
		{
			DirectoryInfo dir = new DirectoryInfo("./modules");

			foreach (FileInfo dl in dir.GetFiles("fitness_*.so"))
				this.comboBoxFitness.Items.Add(dl.Name);

			foreach (FileInfo dl in dir.GetFiles("gene_*.so"))
				this.comboBoxGene.Items.Add(dl.Name);

			foreach (FileInfo dl in dir.GetFiles("mating_*.so"))
				this.comboBoxMating.Items.Add(dl.Name);

			foreach (FileInfo dl in dir.GetFiles("mutator_*.so"))
				this.comboBoxMutator.Items.Add(dl.Name);

			foreach (FileInfo dl in dir.GetFiles("selector_*.so"))
				this.comboBoxSelector.Items.Add(dl.Name);

			this.comboBoxPlotter.Items.Add("SVG");
			this.comboBoxPlotter.SelectedIndex = 0;
		}

		#endregion

		#region Controllers

		private void InitializeControllers()
		{
			this.numericUpDownOffspringRate.Minimum = this.numericUpDownAdultPoolCapacity.Value;
			this.numericUpDownAdultPoolCapacity.ValueChanged += new EventHandler(numericUpDownAdultPoolCapacity_ValueChanged);
			this.textBoxFitness.GotFocus += new EventHandler(textBox_GotFocus);
			this.textBoxFitness.LostFocus += new EventHandler(textBox_LostFocus);
			this.textBoxGene.GotFocus += new EventHandler(textBox_GotFocus);
			this.textBoxGene.LostFocus += new EventHandler(textBox_LostFocus);
			this.textBoxMating.GotFocus += new EventHandler(textBox_GotFocus);
			this.textBoxMating.LostFocus += new EventHandler(textBox_LostFocus);
			this.textBoxMutator.GotFocus += new EventHandler(textBox_GotFocus);
			this.textBoxMutator.LostFocus += new EventHandler(textBox_LostFocus);
			this.textBoxSelector.GotFocus += new EventHandler(textBox_GotFocus);
			this.textBoxSelector.LostFocus += new EventHandler(textBox_LostFocus);
		}

		void textBox_GotFocus(object sender, EventArgs e)
		{
			if (((TextBox)sender).Text.Equals(noParameters))
				((TextBox)sender).Text = string.Empty;
		}

		void numericUpDownAdultPoolCapacity_ValueChanged(object sender, EventArgs e)
		{
			this.numericUpDownOffspringRate.Minimum = this.numericUpDownAdultPoolCapacity.Value;
		}

		void textBox_LostFocus(object sender, EventArgs e)
		{
			if (((TextBox)sender).Text.Trim().Length == 0)
				((TextBox)sender).Text = noParameters;
		}

		#endregion

		#region Helpers

		private void InitializeHelpers()
		{
			this.numericUpDownAdultPoolCapacity.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownAdultPoolCapacity.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownGenerations.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownGenerations.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownLifespan.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownLifespan.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownMatingRate.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownMatingRate.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownMaxProdigies.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownMaxProdigies.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownMutationRate.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownMutationRate.Leave += new EventHandler(component_MouseLeave);

			this.numericUpDownOffspringRate.Enter += new EventHandler(numericUpDown_Enter);
			this.numericUpDownOffspringRate.Leave += new EventHandler(component_MouseLeave);

			this.checkBoxElitism.MouseEnter += new EventHandler(checkBoxElitism_MouseEnter);
			this.checkBoxElitism.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxPlotter.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxPlotter.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxFitness.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxFitness.MouseLeave += new EventHandler(component_MouseLeave);
			this.textBoxFitness.MouseEnter += new EventHandler(textBox_MouseEnter);
			this.textBoxFitness.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxGene.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxGene.MouseLeave += new EventHandler(component_MouseLeave);
			this.textBoxGene.MouseEnter += new EventHandler(textBox_MouseEnter);
			this.textBoxGene.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxMating.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxMating.MouseLeave += new EventHandler(component_MouseLeave);
			this.textBoxMating.MouseEnter += new EventHandler(textBox_MouseEnter);
			this.textBoxMating.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxMutator.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxMutator.MouseLeave += new EventHandler(component_MouseLeave);
			this.textBoxMutator.MouseEnter += new EventHandler(textBox_MouseEnter);
			this.textBoxMutator.MouseLeave += new EventHandler(component_MouseLeave);

			this.comboBoxSelector.MouseEnter += new EventHandler(comboBox_MouseEnter);
			this.comboBoxSelector.MouseLeave += new EventHandler(component_MouseLeave);
			this.textBoxSelector.MouseEnter += new EventHandler(textBox_MouseEnter);
			this.textBoxSelector.MouseLeave += new EventHandler(component_MouseLeave);

			this.buttonLoad.MouseEnter += new EventHandler(button_MouseEnter);
			this.buttonLoad.MouseLeave += new EventHandler(component_MouseLeave);
			this.buttonSave.MouseEnter += new EventHandler(button_MouseEnter);
			this.buttonSave.MouseLeave += new EventHandler(component_MouseLeave);
			this.buttonSaveAs.MouseEnter += new EventHandler(button_MouseEnter);
			this.buttonSaveAs.MouseLeave += new EventHandler(component_MouseLeave);
			this.buttonSaveAndRun.MouseEnter += new EventHandler(button_MouseEnter);
			this.buttonSaveAndRun.MouseLeave += new EventHandler(component_MouseLeave);
		}

		private void component_MouseLeave(object sender, EventArgs e)
		{
			this.toolStripStatusHint.Text = this.hint;
			this.statusStrip.Invalidate();
		}

		private void button_MouseEnter(object sender, EventArgs e)
		{
			switch (((Button)sender).Name)
			{
				case "buttonLoad":
					this.toolStripStatusHint.Text = "Load settings from file";
					break;
				case "buttonSave":
					this.toolStripStatusHint.Text = "Save these settings";
					break;
				case "buttonSaveAs":
					this.toolStripStatusHint.Text = "Save these settings as a new configuration file";
					break;
				case "buttonSaveAndRun":
					this.toolStripStatusHint.Text = "Save these settings and run Ngene";
					break;
			}
		}

		private void checkBoxElitism_MouseEnter(object sender, EventArgs e)
		{
			this.toolStripStatusHint.Text = "Elitism keeps the individual with the highest fitness over generations";
		}

		private void comboBox_MouseEnter(object sender, EventArgs e)
		{
			switch (((ComboBox)sender).Name)
			{
				case "comboBoxPlotter":
					this.toolStripStatusHint.Text = "Choose plotter output";
					break;
				case "comboBoxFitness":
					this.toolStripStatusHint.Text = "Choose a fitness module";
					break;
				case "comboBoxGene":
					this.toolStripStatusHint.Text = "Choose a gene module";
					break;
				case "comboBoxMating":
					this.toolStripStatusHint.Text = "Choose a mating module";
					break;
				case "comboBoxMutator":
					this.toolStripStatusHint.Text = "Choose a mutator module";
					break;
				case "comboBoxSelector":
					this.toolStripStatusHint.Text = "Choose a selector module";
					break;
			}
		}

		private void numericUpDown_Enter(object sender, EventArgs e)
		{
			switch (((NumericUpDown)sender).Name)
			{
				case "numericUpDownAdultPoolCapacity":
					this.toolStripStatusHint.Text = "Set the number of adults per generation";
					break;
				case "numericUpDownGenerations":
					this.toolStripStatusHint.Text = "Set the number of generations";
					break;
				case "numericUpDownLifespan":
					this.toolStripStatusHint.Text = "Set the lifespan of an adult";
					break;
				case "numericUpDownMatingRate":
					this.toolStripStatusHint.Text = "Set the rate of successful mating";
					break;
				case "numericUpDownMaxProdigies":
					this.toolStripStatusHint.Text = "Set the number of offspring replacing adults (when lifespan > 1)";
					break;
				case "numericUpDownMutationRate":
					this.toolStripStatusHint.Text = "Set the rate of mutation";
					break;
				case "numericUpDownOffspringRate":
					this.toolStripStatusHint.Text = "Set the number of offspring produced every generation";
					break;
			}
		}

		private void textBox_MouseEnter(object sender, EventArgs e)
		{
			switch (((TextBox)sender).Name)
			{
				case "textBoxFitness":
					this.toolStripStatusHint.Text = "Specify parameters for the fitness module";
					break;
				case "textBoxGene":
					this.toolStripStatusHint.Text = "Specify parameters for the gene module";
					break;
				case "textBoxMating":
					this.toolStripStatusHint.Text = "Specify parameters for the mating module";
					break;
				case "textBoxMutator":
					this.toolStripStatusHint.Text = "Specify parameters for the mutator module";
					break;
				case "textBoxSelector":
					this.toolStripStatusHint.Text = "Specify parameters for the selector module";
					break;
			}
		}

		#endregion

		#region Buttons

		private void buttonLoad_Click(object sender, EventArgs e)
		{
			using (OpenFileDialog openFileDialog = new OpenFileDialog())
			{
				openFileDialog.Filter = fileDialogFilter;
				if (openFileDialog.ShowDialog() == DialogResult.OK)
				{
					using (Stream s = openFileDialog.OpenFile())
					{
						if (s != null)
						{
							try
							{
								LoadConfiguration(s);
								this.currentConfigurationFile = openFileDialog.FileName;
								this.hint = "Loaded '" + this.currentConfigurationFile + "'";
								component_MouseLeave(sender, e);
							}
							catch (Exception ex)
							{
								MessageBox.Show(ex.Message, "Could not read configuration file", MessageBoxButtons.OK, MessageBoxIcon.Error);
							}
						}
					}
				}
			}
		}

		private void buttonSave_Click(object sender, EventArgs e)
		{
			Save(sender, e);
		}

		private void buttonSaveAs_Click(object sender, EventArgs e)
		{
			if (FormCheck())
				SaveAs(sender, e);
		}

		private void buttonSaveAndRun_Click(object sender, EventArgs e)
		{
			if (Save(sender, e))
			{
				try
				{
					ProcessStartInfo processInfo = new ProcessStartInfo("ngene");
					if (!this.currentConfigurationFile.Equals(ngene_conf))
						processInfo.Arguments = "--config " + this.currentConfigurationFile;
					processInfo.UseShellExecute = true;
					Process.Start(processInfo);
					Application.Exit();
				}
				catch (Win32Exception ex)
				{
					MessageBox.Show("Please make sure you're running the configurator from the same folder.\n\nException: " + ex.Message, "Could not run Ngene", MessageBoxButtons.OK, MessageBoxIcon.Error);
				}
			}
		}

		private bool FormCheck()
		{
			string msg = string.Empty;
			if (this.comboBoxGene.SelectedIndex < 0)
				msg = "You need to choose a gene module.";
			else if (this.comboBoxFitness.SelectedIndex < 0)
				msg = "You need to choose a fitness module.";
			else if (this.comboBoxMating.SelectedIndex < 0)
				msg = "You need to choose a mating module.";
			else if (this.comboBoxMutator.SelectedIndex < 0)
				msg = "You need to choose a mutation module.";
			else if (this.comboBoxSelector.SelectedIndex < 0)
				msg = "You need to choose a selection module.";
			else
				return true;
			MessageBox.Show(msg, "Still missing a module", MessageBoxButtons.OK, MessageBoxIcon.Information);
			return false;
		}

		private bool Save(object sender, EventArgs e)
		{
			if (FormCheck())
			{
				if (this.currentConfigurationFile != string.Empty)
				{
					try
					{
						using (StreamWriter s = new StreamWriter(this.currentConfigurationFile))
						{
							SaveConfiguration(s);
						}
						this.hint = "Saved '" + this.currentConfigurationFile + "'";
						component_MouseLeave(sender, e);
						return true;
					}
					catch { return false; }
				}
				else
					return SaveAs(sender, e);
			}
			else return false;
		}

		private bool SaveAs(object sender, EventArgs e)
		{
			using (SaveFileDialog saveFileDialog = new SaveFileDialog())
			{
				saveFileDialog.Filter = fileDialogFilter;
				if (saveFileDialog.ShowDialog() == DialogResult.OK)
				{
					using (Stream s = saveFileDialog.OpenFile())
					{
						if (s != null)
						{
							try
							{
								SaveConfiguration(s);
								this.currentConfigurationFile = saveFileDialog.FileName;
								this.hint = "Saved to '" + this.currentConfigurationFile + "'";
								component_MouseLeave(sender, e);
								return true;
							}
							catch (Exception ex)
							{
								MessageBox.Show(ex.Message, "Could not write configuration file", MessageBoxButtons.OK, MessageBoxIcon.Error);
							}
						}
					}
				}
			}
			return false;
		}

		#endregion

		#region I/O

		private string ReadConfiguration(ref StreamReader s)
		{
			string c = s.ReadLine().Trim();
			while (c.Length == 0 || c[0] == '#')
				c = s.ReadLine().Trim();
			if (c.IndexOf('#') > 0)
				return c.Substring(0, c.IndexOf('#')).TrimEnd();	// removes trailing comments
			else
				return c;
		}

		private void LoadConfiguration(Stream s)
		{
			LoadConfiguration(new StreamReader(s));
			s.Close();
		}

		private void LoadConfiguration(StreamReader s)
		{
			this.numericUpDownAdultPoolCapacity.Value = int.Parse(ReadConfiguration(ref s));
			this.numericUpDownGenerations.Value = int.Parse(ReadConfiguration(ref s));
			this.checkBoxElitism.Checked = Boolean.Parse(ReadConfiguration(ref s));
			this.numericUpDownLifespan.Value = int.Parse(ReadConfiguration(ref s));
			this.numericUpDownMatingRate.Value = decimal.Parse(ReadConfiguration(ref s));
			this.numericUpDownMaxProdigies.Value = int.Parse(ReadConfiguration(ref s));
			this.numericUpDownMutationRate.Value = decimal.Parse(ReadConfiguration(ref s));
			this.numericUpDownOffspringRate.Value = int.Parse(ReadConfiguration(ref s));

			this.comboBoxGene.SelectedIndex = this.comboBoxGene.Items.IndexOf(ReadConfiguration(ref s));
			this.textBoxGene.Text = ReadConfiguration(ref s);

			this.comboBoxFitness.SelectedIndex = this.comboBoxFitness.Items.IndexOf(ReadConfiguration(ref s));
			this.textBoxFitness.Text = ReadConfiguration(ref s);

			this.comboBoxMating.SelectedIndex = this.comboBoxMating.Items.IndexOf(ReadConfiguration(ref s));
			this.textBoxMating.Text = ReadConfiguration(ref s);

			this.comboBoxMutator.SelectedIndex = this.comboBoxMutator.Items.IndexOf(ReadConfiguration(ref s));
			this.textBoxMutator.Text = ReadConfiguration(ref s);

			this.comboBoxSelector.SelectedIndex = this.comboBoxSelector.Items.IndexOf(ReadConfiguration(ref s));
			this.textBoxSelector.Text = ReadConfiguration(ref s);

			s.Close();
		}

		private void SaveConfiguration(Stream s)
		{
			SaveConfiguration(new StreamWriter(s));
			s.Close();
		}

		private void SaveConfiguration(StreamWriter s)
		{
			s.Write("# Don't change the order of these settings!\n"
				+ this.numericUpDownAdultPoolCapacity.Value.ToString() + "\t\t# adult pool capacity\n"
				+ this.numericUpDownGenerations.Value.ToString() + "\t\t# doomsday\n"
				+ this.checkBoxElitism.Checked.ToString() + "\t# elitism\n"
				+ this.numericUpDownLifespan.Value.ToString() + "\t\t# lifespan\n"
				+ this.numericUpDownMatingRate.Value.ToString() + "\t\t# mating rate\n"
				+ this.numericUpDownMaxProdigies.Value.ToString() + "\t\t# max prodigies\n"
				+ this.numericUpDownMutationRate.Value.ToString() + "\t\t# mutation rate\n"
				+ this.numericUpDownOffspringRate.Value.ToString() + "\t\t# offspring rate\n"
				+ "\n# gene module\n"
				+ this.comboBoxGene.SelectedItem.ToString() + "\n"
				+ this.textBoxGene.Text.Trim() + "\n"
				+ "\n# fitness module\n"
				+ this.comboBoxFitness.SelectedItem.ToString() + "\n"
				+ this.textBoxFitness.Text.Trim() + "\n"
				+ "\n# mating module\n"
				+ this.comboBoxMating.SelectedItem.ToString() + "\n"
				+ this.textBoxMating.Text.Trim() + "\n"
				+ "\n# mutator module\n"
				+ this.comboBoxMutator.SelectedItem.ToString() + "\n"
				+ this.textBoxMutator.Text.Trim() + "\n"
				+ "\n# selector module\n"
				+ this.comboBoxSelector.SelectedItem.ToString() + "\n"
				+ this.textBoxSelector.Text.Trim() + "\n");
			s.Close();
		}

		#endregion
	}
}
