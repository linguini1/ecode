# ecode

I wrote this very simple program in order to help me decode error value when
developing on [Nuttx](github.com/apache/nuttx). Errors there are usually printed
as just numerical values, which I haven't memorized despite seeing constantly.

To see the help information, run `ecode --help`.

## Example

```console
$ ecode 12
12 ENOMEM Out of memory
$ ecode EFAULT
14 EFAULT Bad address
```
