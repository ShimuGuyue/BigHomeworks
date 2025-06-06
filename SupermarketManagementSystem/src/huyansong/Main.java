package huyansong;

import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        Supermarket supermarket = new Supermarket();
        System.out.println("超市经营现在开始！");
        System.out.println("正在进入超市管理系统...");
        System.out.println("*");
        System.out.println("*");
        System.out.println("*");
        System.out.println("超市管理系统进入成功！");

        System.out.println("键入Enter键继续...");
        sc.nextLine();

        while (true) {
            // 用户输入操作类型，系统执行对应操作
            System.out.println("系统菜单如下：");
            System.out.println("1)销售功能      2)添加功能      3)查询功能      4)修改功能");
            System.out.println("5)删除功能      6)统计功能      7)信息存盘      8)信息读取");
            System.out.println("q)退出系统");
            System.out.println("请输入要执行的操作：");
            char mode = sc.nextLine().charAt(0);

            // 判断合适结束循环，退出系统
            boolean work = true;

            switch (mode) {
                case '1':
                    supermarket.Sale_good(sc);
                    break;
                case '2':
                    supermarket.Add_good(sc);
                    break;
                case '3':
                    supermarket.Find_good(sc);
                    break;
                case '4':
                    supermarket.Modify_good(sc);
                    break;
                case '5':
                    supermarket.Delete_good(sc);
                    break;
                case '6':
                    supermarket.Collect_goods();
                    break;
                case '7':
                    supermarket.Save_data();
                    break;
                case '8':
                    supermarket.Load_data();
                    break;
                case 'q':
                    work = false;
                    break;
                default:
                    System.out.println("输入非法！请重新输入！");
            }
            // 当用户按退出键时退出管理系统
            if (!work)
            {
                System.out.println("正在退出超市管理系统...");
                System.out.println("*");
                System.out.println("*");
                System.out.println("*");
                System.out.println("超市管理系统退出成功！");
                break;
            }

            // 等待用户键入Enter键再继续下一次循环，为用户留出反应时间
            System.out.println("操作完成，请键入Enter键继续...");
            sc.nextLine();
            System.out.println();
            System.out.println();
            System.out.println();
        }
        System.out.println("超市经营结束！");
        System.out.println("感谢你的使用！再见！");

        sc.close();
    }
}
