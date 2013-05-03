// TextForm.java
// A simple label/field form panel
//

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;
import java.net.*;

public class TextForm extends JPanel {

    private String[] labels = { "First Name", "Middle Initial", "Last Name", "Age" };
    private char[] mnemonics = { 'F', 'M', 'L', 'A' };
    private int[] widths = { 15, 1, 15, 3 };
    private String[] tips = { "First Name", "Middle Initial", "Last Name", "Age" };
    protected DataOutputStream outToServer = null;
    protected Socket clientSocket = null;

  private JTextField[] fields;

  // Create a form with the specified labels, tooltips, and sizes.
  public TextForm() {
    super(new BorderLayout());
    JPanel labelPanel = new JPanel(new GridLayout(labels.length, 1));
    JPanel fieldPanel = new JPanel(new GridLayout(labels.length, 1));
    add(labelPanel, BorderLayout.WEST);
    add(fieldPanel, BorderLayout.CENTER);
    fields = new JTextField[labels.length];

    for (int i=0; i < labels.length; i+=1) {
      fields[i] = new JTextField();
      if (i < tips.length) fields[i].setToolTipText(tips[i]);
      if (i < widths.length) fields[i].setColumns(widths[i]);

      JLabel lab = new JLabel(labels[i], JLabel.RIGHT);
      lab.setLabelFor(fields[i]);
      if (i < mnemonics.length) lab.setDisplayedMnemonic(mnemonics[i]);

      labelPanel.add(lab);
      JPanel p = new JPanel(new FlowLayout(FlowLayout.LEFT));
      p.add(fields[i]);
      fieldPanel.add(p);
    }
  }

  public String getText(int i) {
    return( fields[i].getText() );
  }

public void start() throws Exception {

  String sentence;
  String modifiedSentence;
  BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in));
  //clientSocket = new Socket("localhost", 6789);


    JButton submit = new JButton("Submit Form");
    JFrame f = new JFrame("Text Form Example");
    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    f.getContentPane().add(this, BorderLayout.NORTH);
    JPanel p = new JPanel();
    p.add(submit);
    f.getContentPane().add(p, BorderLayout.SOUTH);
    f.pack();
    f.setVisible(true);

    /*submit.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
try {
System.out.println("Writing: " + getText(0));
  outToServer = new DataOutputStream(clientSocket.getOutputStream());
          outToServer.writeBytes(getText(0));
} catch (Exception j) {System.out.println(j);}
        }
      });*/

//clientSocket.close();



}

  public static void main(String[] args) throws Exception {
	new TextForm().start();
  }
}
