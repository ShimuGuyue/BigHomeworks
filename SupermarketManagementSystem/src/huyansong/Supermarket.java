package huyansong;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

// 定义超市类
public class Supermarket {
    // 将所有商品按类别放到四个集合里作为超市的一个元素
    Map<String, Set<Good>> goods;

    public Supermarket() {
        goods = new java.util.HashMap<>();
    }

    /*  菜单功能
     * 用户输入参数，系统调用方法。
     * */
    public void Menu() throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.println("正在进入超市管理系统...");
        System.out.println("*");
        System.out.println("*");
        System.out.println("*");
        System.out.println("超市管理系统进入成功！");
        System.out.println("键入Enter键继续...");
        sc.nextLine();

        while (true){
            // 用户输入操作类型，系统执行对应操作
            System.out.println("系统菜单如下：");
            System.out.println("1)销售功能      2)添加功能      3)查询功能      4)修改功能");
            System.out.println("5)删除功能      6)统计功能      7)信息存盘      8)信息读取");
            System.out.println("q)退出系统");
            System.out.println("请输入要执行的操作：");
            String mode = sc.nextLine();

            // 判断何时结束循环，退出系统
            boolean work = true;

            switch (mode) {
                case "1":
                    this.Sale_good(sc);
                    break;
                case "2":
                    this.Add_good(sc);
                    break;
                case "3":
                    this.Find_good(sc);
                    break;
                case "4":
                    this.Modify_good(sc);
                    break;
                case "5":
                    this.Delete_good(sc);
                    break;
                case "6":
                    this.Collect_goods();
                    break;
                case "7":
                    this.Save_data();
                    break;
                case "8":
                    this.Load_data();
                    break;
                case "q":
                    work = false;
                    break;
                default:
                    System.out.println("输入非法！请重新输入！");
            }
            // 当用户按退出键时退出管理系统
            if (!work){
                System.out.println("正在退出超市管理系统...");
                System.out.println("*");
                System.out.println("*");
                System.out.println("*");
                System.out.println("超市管理系统退出成功！");
                break;
            }

            // 等待用户键入Enter键再继续下一次循环，为用户留出反应时间
            System.out.println("[请键入Enter键继续...]");
            sc.nextLine();
            System.out.println();
            System.out.println();
            System.out.println();
        }

        sc.close();
    }

    /*  销售功能
     * 购买商品时，先输入类别，然后输入商品名称，并在库存中查找该商品的相关信息。
     * 如果有库存量，输入购买的数量，进行相应计算。
     * 如果库存量不够，给出提示信息，结束购买。
     * */
    private void Sale_good(Scanner sc){
        // 按类别查找商品
        System.out.println("请输入您要购买的商品类别：");
        String type = sc.nextLine();
        Set<Good> good_set = goods.get(type);
        if (good_set == null) {
            System.out.println("该商品类别不存在！");
            return;
        }

        // 按名称查找商品
        System.out.println("请输入您要购买的商品名称：");
        String name = sc.nextLine();
        Good good = null;
        for(Good g : good_set){
            if(g.name.equals(name)){
                good = g;
                break;
            }
        }
        if (good == null) {
            System.out.println("该商品不存在！");
            return;
        }

        // 计算库余量
        System.out.println("请输入您要购买的商品数量：");
        int num = Integer.parseInt(sc.nextLine());
        if (num > good.remain){
            System.out.println("很抱歉，该商品库余量不足！");
            return;
        }
        // 更新库存量
        good.remain -= num;
        // 计算总价
        int price = num * good.price;
        System.out.println("您一共消费" + price + "元！感谢惠顾！");
    }

    /*  添加功能
     * 主要完成商品信息的添加。
     * */
    private void Add_good(Scanner sc){
        System.out.println("请输入商品类别：");
        String type = sc.nextLine();
        System.out.println("请输入商品名称：");
        String name = sc.nextLine();
        System.out.println("请输入商品价格：");
        int price = Integer.parseInt(sc.nextLine());
        System.out.println("请输入商品库存量：");
        int remain = Integer.parseInt(sc.nextLine());
        System.out.println("请输入生产厂家：");
        String manufacturer = sc.nextLine();
        System.out.println("请输入品牌：");
        String brand = sc.nextLine();

        Good good = new Good(type, name, price, remain, manufacturer, brand);
        goods.computeIfAbsent(type, k -> new java.util.HashSet<>()).add(good);

        System.out.println("商品添加成功！");
    }

    /*  查询功能
     * 可按商品类别、商品名称、生产厂家进行查询。
     * 若存在相应信息，输出所查询的信息；
     * 若不存在该记录，则提示“该记录不存在！”。
     * */
    // 方法变种1：用于用户查找物品
    private void Find_good(Scanner sc){
        System.out.println("请输入您要查询的商品类别：");
        String type = sc.nextLine();
        System.out.println("请输入您要查询的商品名称：");
        String name = sc.nextLine();
        System.out.println("请输入您要查询的生产厂家：");
        String manufacturer = sc.nextLine();

        // 判断是否存在查询的商品类别
        Set<Good> good_set = goods.get(type);
        if (good_set == null) {
            System.out.println("该记录不存在！");
            return;
        }
        // 判断是否存在查询的商品名称和生产厂家
        Good good = null;
        for (Good g : good_set) {
            if (g.name.equals(name) && g.manufacturer.equals(manufacturer)) {
                good = g;
                break;
            }
        }
        if (good == null) {
            System.out.println("该记录不存在！");
            return;
        }

        // 若查询到商品信息，则输出查询结果
        System.out.println("查询结果：");
        System.out.println("[类别：" + good.type + "]");
        System.out.println("[名称：" + good.name + "]");
        System.out.println("[价格：" + good.price + "]");
        System.out.println("[库存量：" + good.remain + "]");
        System.out.println("[生产厂家：" + good.manufacturer + "]");
        System.out.println("[品牌：" + good.brand + "]");
    }
    // 方法变种2：用于其他函数调用
    private Good Find_good(String type, String name) {

        // 判断是否存在查询的商品类别
        Set<Good> good_set = goods.get(type);
        if (good_set == null) {
            return null;
        }
        // 判断是否存在查询的商品名称和生产厂家
        Good good = null;
        for (Good g : good_set) {
            if (g.name.equals(name)) {
                good = g;
                break;
            }
        }
        return good;
    }

    /*  修改功能
     * 根据查询结果对相应的记录进行修改。
     * */
    private void Modify_good(Scanner sc) {
        System.out.println("请输入您要修改的商品类别：");
        String type0 = sc.nextLine();
        System.out.println("请输入您要修改的商品名称：");
        String name0 = sc.nextLine();
        Good good = Find_good(type0, name0);
        if (good == null) {
            System.out.println("没有查询到商品信息，修改失败！");
            return;
        }

        System.out.println("请更新商品类别（当前：" + good.type + "）：");
        String type = sc.nextLine();
        System.out.println("请更新商品名称（当前：" + good.name + "）：");
        String name = sc.nextLine();
        System.out.println("请更新商品价格（当前：" + good.price + "）：");
        int price = Integer.parseInt(sc.nextLine());
        System.out.println("请更新商品库存量（当前：" + good.remain + "）：");
        int remain = Integer.parseInt(sc.nextLine());
        System.out.println("请更新生产厂家（当前：" + good.manufacturer + "）：");
        String manufacturer = sc.nextLine();
        System.out.println("请更新品牌（当前：" + good.brand + "）：");
        String brand = sc.nextLine();

        // 更新商品信息
        good.type = type;
        good.name = name;
        good.price = price;
        good.remain = remain;
        good.manufacturer = manufacturer;
        good.brand = brand;

        System.out.println("商品信息修改成功！");
    }

    /*  删除功能
     * 主要完成商品信息的删除。
     * 先输入商品类别，再输入要删除的商品名称，根据查询结果删除该物品的记录。
     * 如果该商品不在物品库中，则提示“该商品不存在”。
     * */
    private void Delete_good(Scanner sc){
        System.out.println("请输入您要删除的商品类别：");
        String type = sc.nextLine();
        System.out.println("请输入您要删除的商品名称：");
        String name = sc.nextLine();

        Good good = Find_good(type, name);
        if (good == null) {
            System.out.println("该商品不存在！");
            return;
        }

        // 删除商品信息
        Set<Good> good_set = goods.get(type);
        good_set.remove(good);
        if (good_set.isEmpty())
            goods.remove(type);
        System.out.println("商品信息删除成功！");
    }

    /*  统计功能
     * 收集所有商品信息，按库存量从高到低排序，并输出结果。
     * */
    private void Collect_goods(){
        System.out.println("正在整理商品信息...");
        System.out.println("*");
        System.out.println("*");
        System.out.println("*");
        System.out.println("商品信息整理结果如下：");

        // 收集所有商品
        java.util.List<Good> all_goods = new java.util.ArrayList<>();
        for (Set<Good> set : goods.values()) {
            all_goods.addAll(set);
        }
        int sum = all_goods.size();
        System.out.println("当前库存商品总数：" + sum);
        if (sum == 0)
            return;

        // 按库存量从高到低排序
        all_goods.sort((a, b) -> Integer.compare(b.remain, a.remain));

        // 按 json 的格式输出商品信息
        System.out.println("商品信息按库存量从高到低排序如下：");
        System.out.println("[");
        for (int i = 0; i < all_goods.size(); i++) {
            Good g = all_goods.get(i);
            System.out.println("\t{");
            System.out.println("\t\t" + "类别: " + g.type + ",");
            System.out.println("\t\t" + "名称: " + g.name + ",");
            System.out.println("\t\t" + "价格: " + g.price + ",");
            System.out.println("\t\t" + "库存量: " + g.remain + ",");
            System.out.println("\t\t" + "生产厂家: " + g.manufacturer + ",");
            System.out.println("\t\t" + "品牌: " + g.brand);
            System.out.print  ("\t}");
            if (i != all_goods.size() - 1) {
                System.out.println(",");
            } else {
                System.out.println();
            }
        }
        System.out.println("]");
    }

    /*  导出信息
     * 将商品信息写入文件。
     * */
    private void Save_data() throws IOException {
        System.out.println("正在导出商品信息...");
        System.out.println("*");
        System.out.println("*");
        System.out.println("*");

        // 将商品信息写入文件
        java.io.BufferedWriter bw = new java.io.BufferedWriter(new java.io.FileWriter("resources/data/StoreHouse.txt"));
        for (Set<Good> set : goods.values()) {
            for (Good g : set) {
                bw.write(g.type + " " + g.name + " " + g.price + " " + g.remain + " " + g.manufacturer + " " + g.brand);
                bw.newLine();
            }
        }
        bw.close();
        System.out.println("商品信息导出成功！");
    }

    /*  读入信息
     * 从文件中将商品信息读入程序。
     * */
    private void Load_data() throws IOException {
        goods.clear();

        System.out.println("正在导入商品信息...");
        System.out.println("*");
        System.out.println("*");
        System.out.println("*");

        // 从文件中读取商品信息
        BufferedReader br = new BufferedReader(new FileReader("resources/data/StoreHouse.txt"));
        String line;
        while ((line = br.readLine()) != null) {
            // 将读取到的商品信息按空格分割，然后创建Good对象
            String[] arr = line.split("\\s+");
            String type = arr[0];
            String name = arr[1];
            int price = Integer.parseInt(arr[2]);
            int remain = Integer.parseInt(arr[3]);
            String manufacturer = arr[4];
            String brand = arr[5];
            Good good = new Good(type, name, price, remain, manufacturer, brand);
            goods.computeIfAbsent(type, k -> new java.util.HashSet<>()).add(good);
        }
        br.close();

        System.out.println("商品信息加载成功！");
    }
}
