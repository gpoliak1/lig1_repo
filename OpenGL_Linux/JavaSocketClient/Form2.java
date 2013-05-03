import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
 
class Form2 extends JFrame implements ActionListener
{
 JButton SUBMIT;
 JPanel panel;
 JLabel label1,label2;
 final JTextField  text1,text2;
     protected DataOutputStream outToServer = null;
    protected Socket clientSocket = null;
 
  Form2()
  {
    BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in));
	
	try {
    clientSocket = new Socket("localhost", 6789);
	} catch (Exception e) {
		System.out.println(e);
	}
  
  
  label1 = new JLabel();
  label1.setText("Command:");
  text1 = new JTextField(15);

  label2 = new JLabel();
  label2.setText("Unused:");
  text2 = new JPasswordField(15);
 
  SUBMIT=new JButton("SUBMIT");
  
  UIManager.put("Button.defaultButtonFollowsFocus", Boolean.TRUE);
  
  panel=new JPanel(new GridLayout(3,1));
  panel.add(label1);
  panel.add(text1);
  panel.add(label2);
  panel.add(text2);
  panel.add(SUBMIT);
  add(panel,BorderLayout.CENTER);
  SUBMIT.addActionListener(this);
  setTitle("OpenGL Command Console");
  }
  

  
 public void actionPerformed(ActionEvent ae)
  {
try {
System.out.println("Writing: " + text1.getText());
  outToServer = new DataOutputStream(clientSocket.getOutputStream());
          outToServer.writeBytes(text1.getText());
} catch (Exception j) {System.out.println(j);}
        }


  public static void main(String arg[])
  {
  try
  {
  Form2 frame=new Form2();
  frame.setSize(300,100);
  frame.setVisible(true);
  }
  catch(Exception e)
  {JOptionPane.showMessageDialog(null, e.getMessage());}
  }

}