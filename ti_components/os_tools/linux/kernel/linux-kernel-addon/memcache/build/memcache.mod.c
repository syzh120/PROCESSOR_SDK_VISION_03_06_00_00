#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x1a6ed8b1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x35b82493, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xff204b6c, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x3abb26b0, __VMLINUX_SYMBOL_STR(ioremap_wc) },
	{ 0x1afae5e7, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x79c5a9f0, __VMLINUX_SYMBOL_STR(ioremap) },
	{ 0xf518658a, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x9dd53e3d, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xe9ccfcd3, __VMLINUX_SYMBOL_STR(ioremap_cache) },
	{ 0x5dcf6341, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "96CA6ED76A008420EC335D8");
