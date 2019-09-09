unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  Buttons, Types, Windows;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Memo1: TMemo;
    Panel1: TPanel;
    Panel2: TPanel;
    SpeedButton1: TSpeedButton;
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Edit4Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Panel1Click(Sender: TObject);
    procedure Panel2Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure ToggleBox1Change(Sender: TObject);
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
  '+': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) + StrToFloat(Edit2.Text));
  '-': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) - StrToFloat(Edit2.Text));
  '*': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) * StrToFloat(Edit2.Text));
  '/': Edit3.Text:= FloatToStr(StrToFloat(Edit1.Text) / StrToFloat(Edit2.Text)); //div
  end;
  Memo1.Text := Memo1.Text + Edit1.Text + ComboBox1.Text + Edit2.Text + '=' + Edit3.Text + chr(13) + chr(10);     // \r\n
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
  Edit1.Text := Edit3.Text;
end;

procedure TForm1.BitBtn2Click(Sender: TObject);
begin
  Edit2.Text := Edit3.Text;
end;

procedure TForm1.Button1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
 case button of
       mbleft :       ;
       mbright:Memo1.Text := '';
  end;
end;

procedure TForm1.Edit4Click(Sender: TObject);
begin
 Edit1.Text := Edit3.Text;
end;


procedure TForm1.FormCreate(Sender: TObject);
begin
  Memo1.Text := '';
end;

procedure TForm1.Panel1Click(Sender: TObject);
begin
  Edit1.Text := Edit3.Text;
end;

procedure TForm1.Panel2Click(Sender: TObject);
begin
  Edit2.Text := Edit3.Text;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
  Form1.Close;
end;

procedure TForm1.ToggleBox1Change(Sender: TObject);
begin

end;

end.

