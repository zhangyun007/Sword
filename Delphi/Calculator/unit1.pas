unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
begin
  case ComboBox1.Text of
  '+': Edit3.Text:= IntToStr(StrToInt(Edit1.Text) + StrToInt(Edit2.Text));
  '-': Edit3.Text:= IntToStr(StrToInt(Edit1.Text) - StrToInt(Edit2.Text));
  '*': Edit3.Text:= IntToStr(StrToInt(Edit1.Text) * StrToInt(Edit2.Text));
  '/': Edit3.Text:= FloatToStr(StrToInt(Edit1.Text) / StrToInt(Edit2.Text)); //div
  end;
  Memo1.Text := Memo1.Text + Edit1.Text + ComboBox1.Text + Edit2.Text + '=' + Edit3.Text + chr(13) + chr(10);     // \r\n
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  Memo1.Text := '';
end;

end.

