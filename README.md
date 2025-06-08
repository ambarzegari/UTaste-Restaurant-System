AP HTTP
===

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/AP-ECE-UT/APHTTP/license.md)
[![Release](https://img.shields.io/github/release/AP-ECE-UT/APHTTP.svg?color=brightgreen)](https://github.com/AP-ECE-UT/APHTTP/releases/latest)
[![Wiki](https://img.shields.io/badge/GitHub-Wiki-red.svg)](https://github.com/AP-ECE-UT/APHTTP/wiki)

**AP HTTP::_server_** is a simple web application server-side blocking framework for C++.  
This library is based on simplified versions of [W++](http://konteck.github.io/wpp/), [HappyHTTP](http://scumways.com/happyhttp/happyhttp.html), and [cpp-netlib](http://cpp-netlib.org/).


# سیستم رزرو رستوران UTaste

پیاده‌سازی یک سیستم کامل رزرو رستوران در سه فاز مجزا با استفاده از C++


## ویژگی‌های اصلی

### فاز 1: پایه‌ای
- سیستم ثبت نام و ورود کاربران
- مدیریت محله‌ها و رستوران‌ها
- قابلیت جستجو و رزرو رستوران‌ها
- نمایش منوها و زمان‌بندی رزروها

### فاز 2: پیشرفته
- سیستم کیف پول کاربران
- مکانیزم‌های مختلف تخفیف‌دهی
- محاسبه خودکار هزینه‌ها با اعمال تخفیف‌ها
- گزارش‌گیری پیشرفته

### فاز 3: وب‌محور
- رابط کاربری مبتنی بر وب با HTML/CSS
- سیستم session برای مدیریت کاربران
- APIهای RESTful برای دسترسی به داده‌ها
- گزارش‌های تحلیلی




# ثبت نام کاربر
POST signup ? username "user1" password "pass123"

# ورود به سیستم
POST login ? username "user1" password "pass123"

# جستجوی رستوران
GET restaurants ? food_name "Pizza"

# رزرو میز
POST reserve ? restaurant_name "PizzaHouse" table_id "3" start_time "19" end_time "21" foods "Pizza,Margarita"
