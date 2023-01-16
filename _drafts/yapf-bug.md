
test.py:

```python
# Works
a: tuple[int, int] = (1, 2)
print(f'{type(a)=}')

# Crashes
b: tuple[int, int] = 1, 2
print(f'{type(b)=}')
```

```console
% python3 test.py
type(a)=<class 'tuple'>
type(b)=<class 'tuple'>
```

```console
% yapf test.py
Traceback (most recent call last):
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/pytree_utils.py", line 119, in ParseCodeToTree
    tree = parser_driver.parse_string(code, debug=False)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/driver.py", line 103, in parse_string
    return self.parse_tokens(tokens, debug)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/driver.py", line 71, in parse_tokens
    if p.addtoken(type, value, (prefix, start)):
       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/parse.py", line 162, in addtoken
    raise ParseError("bad input", type, value, context)
lib2to3.pgen2.parse.ParseError: bad input: type=12, value=',', context=('', (6, 22))

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/yapf_api.py", line 183, in FormatCode
    tree = pytree_utils.ParseCodeToTree(unformatted_source)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/pytree_utils.py", line 125, in ParseCodeToTree
    tree = parser_driver.parse_string(code, debug=False)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/driver.py", line 103, in parse_string
    return self.parse_tokens(tokens, debug)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/driver.py", line 71, in parse_tokens
    if p.addtoken(type, value, (prefix, start)):
       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/python@3.11/3.11.1/Frameworks/Python.framework/Versions/3.11/lib/python3.11/lib2to3/pgen2/parse.py", line 162, in addtoken
    raise ParseError("bad input", type, value, context)
lib2to3.pgen2.parse.ParseError: bad input: type=12, value=',', context=('', (6, 22))

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/__init__.py", line 225, in _FormatFile
    reformatted_code, encoding, has_change = yapf_api.FormatFile(
                                             ^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/yapf_api.py", line 96, in FormatFile
    reformatted_source, changed = FormatCode(
                                  ^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/yapf_api.py", line 186, in FormatCode
    raise errors.YapfError(errors.FormatErrorMsg(e))
                           ^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/errors.py", line 37, in FormatErrorMsg
    return '{}:{}:{}: {}'.format(e.args[1][0], e.args[1][1], e.args[1][2], e.msg)
                                 ~~~~~~^^^
IndexError: tuple index out of range

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/homebrew/bin/yapf", line 33, in <module>
    sys.exit(load_entry_point('yapf==0.32.0', 'console_scripts', 'yapf')())
             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/__init__.py", line 360, in run_main
    sys.exit(main(sys.argv))
             ^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/__init__.py", line 124, in main
    changed = FormatFiles(
              ^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/__init__.py", line 202, in FormatFiles
    changed |= _FormatFile(filename, lines, style_config, no_local_style,
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/__init__.py", line 236, in _FormatFile
    raise errors.YapfError(errors.FormatErrorMsg(e))
                           ^^^^^^^^^^^^^^^^^^^^^^^^
  File "/opt/homebrew/Cellar/yapf/0.32.0/libexec/lib/python3.11/site-packages/yapf/yapflib/errors.py", line 37, in FormatErrorMsg
    return '{}:{}:{}: {}'.format(e.args[1][0], e.args[1][1], e.args[1][2], e.msg)
                                 ~~~~~~^^^
IndexError: tuple index out of range
```
