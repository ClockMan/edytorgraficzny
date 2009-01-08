object cfgWin: TcfgWin
  Left = 192
  Top = 114
  BorderStyle = bsToolWindow
  Caption = 'Bitrate'
  ClientHeight = 116
  ClientWidth = 129
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object bit1: TRadioButton
    Left = 8
    Top = 8
    Width = 49
    Height = 17
    Caption = '1 bit'
    TabOrder = 0
  end
  object bit4: TRadioButton
    Left = 8
    Top = 32
    Width = 49
    Height = 17
    Caption = '4 bit'
    TabOrder = 1
  end
  object bit8: TRadioButton
    Left = 8
    Top = 56
    Width = 49
    Height = 17
    Caption = '8 bit'
    TabOrder = 2
  end
  object bit16: TRadioButton
    Left = 72
    Top = 8
    Width = 49
    Height = 17
    Caption = '16 bit'
    TabOrder = 3
  end
  object bit24: TRadioButton
    Left = 72
    Top = 32
    Width = 49
    Height = 17
    Caption = '24 bit'
    Checked = True
    TabOrder = 4
    TabStop = True
  end
  object bit32: TRadioButton
    Left = 72
    Top = 56
    Width = 49
    Height = 17
    Caption = '32 bit'
    TabOrder = 5
  end
  object OK: TButton
    Left = 32
    Top = 83
    Width = 57
    Height = 25
    Caption = 'OK'
    TabOrder = 6
    OnClick = OKClick
  end
end
