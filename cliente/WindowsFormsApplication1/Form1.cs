using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Cliente : Form
    {
        Socket server;
        public Cliente()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

           
        }

        private void AtenderServidor()
        {
            bool fin = false;

            while (!fin)
            {


                byte[] msg1 = new byte[100];
                server.Receive(msg1);
                string message = Encoding.ASCII.GetString(msg1).Split('\0')[0];
                string[] trozos = message.Split('-');
                int codigo = Convert.ToInt32(trozos[0]);
                string mensaje = trozos[1];

                switch (codigo)
                {
                    case 0:
                        string[] trozos1 = mensaje.Split('/');
                        int code = Convert.ToInt32(trozos1[0]);
                        if (code == 0) 
                        { 
                            
                        }


                        break;


                }
            }

        }
        private void button1_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse(IP.Text);
            IPEndPoint ipep = new IPEndPoint(direc, 9050);
            

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

            }
            catch (SocketException ex)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Longitud.Checked)
            {
                string mensaje = "1/" + parameter.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split (',')[0];
                MessageBox.Show("La longitud de tu nombre es: " + mensaje);
            }
            else
            {
                string mensaje = "2/" + parameter.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];
              

                if (mensaje=="SI")
                    MessageBox.Show("Tu nombre ES bonito.");
                else
                    MessageBox.Show("Tu nombre NO bonito. Lo siento.");

            }

            // Se terminó el servicio. 
            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            string user = textBoxUsername.Text;
            string pass = textBoxPassword.Text;
            string SQL_query;
            string answer;
            if (user == "" || pass == "")
            {
                MessageBox.Show("Por favor introduzca un nombre de usuario y contraseña");
            }
            else
            {

                //string mensaje = "1/" + parameter.Text;
                SQL_query = "1/"+user+"/"+pass+"/NULL";

                string mensaje = "1/" + parameter.Text;
                SQL_query = "1/"+user+"/"+pass;

                byte[] SQLserver = System.Text.Encoding.ASCII.GetBytes(SQL_query);                              
                server.Send(SQLserver);
                byte[] msg2 = new byte[200];
                server.Receive(msg2);
                answer = Encoding.ASCII.GetString(msg2).Split('\0')[0] ;
                //int answerint = Convert.ToInt32(answer);
                if (answer == "Si")
                {
                    MessageBox.Show("Bienvenido " + user + ", has iniciado sesión correctamente");
                    textBoxUsername.Text = "";
                    textBoxPassword.Text =  "";
                }
                else if (answer == "No")
                {
                    MessageBox.Show("El nombre de usuario o contraseña son incorrectos o no existen");
                }
                
            }
        }

        private void buttonSingUp_Click(object sender, EventArgs e)
        {
            string name = textBoxName.Text;
            string user = textBoxUserLog.Text;
            string pass1 = textBoxPasswordLog1.Text;
            string pass2 = textBoxPasswordLog2.Text;
            string SQL_query;
            string answer;
            if (user == "" || pass1 == "" || pass2 == "")
            {
                MessageBox.Show("Por favor, rellene todos los campos");
            }
            else if(pass1 != pass2) MessageBox.Show("Las contraseñas no coinciden");
            else
            {
                //string mensaje = "1/" + parameter.Text;
                SQL_query = "3/" + name + "/" + user + "/" + pass1;
                byte[] SQLserver = System.Text.Encoding.ASCII.GetBytes(SQL_query);
                server.Send(SQLserver);
                byte[] msg2 = new byte[200];
                server.Receive(msg2);
                answer = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                //int answerint = Convert.ToInt32(answer);
                if (answer == "Si")
                {
                    MessageBox.Show("Bienvenido " + user + ", te has registrado correctamente");
                    textBoxName.Text = "";
                    textBoxUserLog.Text = "";
                    textBoxPasswordLog1.Text = "";
                    textBoxPasswordLog2.Text = "";
                }
                else if (answer == "No")
                {
                    MessageBox.Show("Ha ocurrido un error al registrarse");
                }

            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            string user = textBoxUserDelete.Text;
            string pass = textBoxPassDelete.Text;
            string SQL_query;
            string answer;
            if (user == "" || pass == "")
            {
                MessageBox.Show("Por favor, rellene todos los campos");
            }
            SQL_query = "2/" + user + "/" + pass;
            byte[] SQLserver = System.Text.Encoding.ASCII.GetBytes(SQL_query);
            server.Send(SQLserver);
            byte[] msg2 = new byte[200];
            server.Receive(msg2);
            answer = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            //int answerint = Convert.ToInt32(answer);
            if (answer == "Si")
            {
                MessageBox.Show("El usuario " + user + " ha sido eliminado correctamente");
          
                textBoxUserDelete.Text = "";
                textBoxPassDelete.Text = "";
            }
            else if (answer == "No")
            {
                MessageBox.Show("Ha ocurrido un error al registrarse");
            }
        }
    }
}
