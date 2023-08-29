import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class SystemInfo {

    public static void main(String[] args) {
        display();
    }

    public static void display() {
        System.out.println("(\\_/)\t\u001B[0;33m uptime: " + uptime() + "\u001B[0;0m"); // uptime - orange
        System.out.println("(oᴥo)\t\u001B[0;31m shell: " + shell() + "\u001B[0;0m"); // shell - red
        System.out.println("|U°U|\t\u001B[0;35m distro: " + distro() + "\u001B[0;0m"); // distro - purple
        System.out.println("|   |\t\u001B[0;34m hostname: " + hostname() + "\u001B[0;0m"); // host - blue
        System.out.println("'U_U'\t\u001B[0;36m kernel: " + kernel() + "\u001B[0;0m"); // kernel - cyan
        System.out.println("  U");
    }

    public static String shell() {
        return System.getenv("SHELL");
    }

    public static String uptime() {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("/proc/uptime"));
            String line = reader.readLine();
            reader.close();
            String[] parts = line.split(" ");
            double uptimeSeconds = Double.parseDouble(parts[0]);

            int days = (int) uptimeSeconds / 86400;
            int hours = (int) (uptimeSeconds % 86400) / 3600;
            int minutes = (int) (uptimeSeconds % 3600) / 60;
            int seconds = (int) uptimeSeconds % 60;
            int milliseconds = (int) ((uptimeSeconds - Math.floor(uptimeSeconds)) * 1000);

            return String.format("%d Days, %dh %dm %ds.%d", days, hours, minutes, seconds, milliseconds);
        } catch (IOException e) {
            e.printStackTrace();
            return "";
        }
    }

    public static String distro() {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("/etc/issue"));
            String distro = reader.readLine();
            reader.close();
            return distro.replace("\\n", "").replace("\\l", "").replace("\\r", "").replace("()", ""); // Somehow the file contains certain characters in certain distros.
        } catch (IOException e) {
            e.printStackTrace();
            return "";
        }
    }

    public static String hostname() {
        try {
            return InetAddress.getLocalHost().getHostName();
        } catch (UnknownHostException e) {
            e.printStackTrace();
            return "";
        }
    }

    public static String kernel() {
        return System.getProperty("os.name") + " " + System.getProperty("os.version");
    }
}