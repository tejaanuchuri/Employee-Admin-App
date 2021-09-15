using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Collections.Generic;
using System.Configuration;
using System.Data.OleDb;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;



namespace WPFControls
{
    /// <summary>
    /// Interaction logic for AnimClock.xaml
    /// </summary>
    public partial class AnimClock : Page
    {
        //private DispatcherTimer _dayTimer;

        public AnimClock()
        {
            InitializeComponent();
            LoadEmployeeRecordsOnGrid();
        }
        public void LoadEmployeeRecordsOnGrid()
        {
            OleDbConnection connection = new OleDbConnection();
            connection.ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Persist Security Info=False;";
            connection.Open();
            OleDbCommand command = new OleDbCommand();
            command.CommandText = "Select * from EmployeeTable";
            command.Connection = connection;
            OleDbDataReader rd = command.ExecuteReader();
            datagrid.ItemsSource = rd;
        }
    }
}
