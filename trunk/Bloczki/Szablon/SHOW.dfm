object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Config'
  ClientHeight = 219
  ClientWidth = 326
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 80
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Zapisz'
    TabOrder = 0
  end
  object Button2: TButton
    Left = 161
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 1
    OnClick = Button2Click
  end
end
