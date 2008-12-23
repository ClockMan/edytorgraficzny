object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 183
  ClientWidth = 329
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Cancel: TButton
    Left = 176
    Top = 150
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 0
    OnClick = CancelClick
  end
  object OK: TButton
    Left = 80
    Top = 150
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = OKClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 313
    Height = 89
    Caption = 'Bitrate obrazu'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object bit_4: TRadioButton
      Left = 16
      Top = 56
      Width = 89
      Height = 17
      Caption = '4 bit na piksel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object bit_1: TRadioButton
      Left = 16
      Top = 33
      Width = 89
      Height = 17
      Caption = '1 bit na piksel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object bit_16: TRadioButton
      Left = 111
      Top = 56
      Width = 99
      Height = 17
      Caption = '16 bit na piksel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object bit_24: TRadioButton
      Left = 207
      Top = 33
      Width = 98
      Height = 17
      Caption = '24 bit na piksel'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      TabStop = True
    end
    object bit_32: TRadioButton
      Left = 207
      Top = 56
      Width = 98
      Height = 17
      Caption = '32 bit na piksel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object bit_8: TRadioButton
      Left = 111
      Top = 33
      Width = 90
      Height = 17
      Caption = '8 bit na piksel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
  end
  object Button1: TButton
    Left = 8
    Top = 103
    Width = 75
    Height = 25
    Caption = 'Zapisz w...'
    TabOrder = 3
    OnClick = Button1Click
  end
  object EditPath: TEdit
    Left = 89
    Top = 107
    Width = 232
    Height = 21
    ReadOnly = True
    TabOrder = 4
  end
  object SaveDialog1: TSaveDialog
    Left = 272
    Top = 144
  end
end
